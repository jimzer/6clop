import sobol_seq
import numpy as np
from abc import ABC, abstractmethod


def scale_matrix(s):
    mat = np.zeros((4, 4))
    mat[0][0] = s[0]
    mat[1][1] = s[1]
    mat[2][2] = s[2]
    mat[3][3] = 1
    return mat


def translate_matrix(t):
    mat = np.identity(4)
    mat[0][3] = t[0]
    mat[1][3] = t[1]
    mat[2][3] = t[2]
    return mat


class Transform:
    def __init__(self, matrix=None):
        self.mat = matrix
        self.inv_mat = np.linalg.inv(matrix)

    def transform(self, vec):
        vec_h = np.ones(4)
        vec_h[:3] = vec
        res = self.mat @ vec_h
        return res[:3]

    def inv_transform(self, vec):
        vec_h = np.ones(4)
        vec_h[:3] = vec
        res = self.inv_mat @ vec_h
        return res[:3]


def compose(*args):
    m = args[0]
    for x in args[1:]:
        m = m @ x
    return Transform(m)


def raster_to_ndc(res_x, res_y):
    s = [1 / res_x, 1 / res_y, 1]
    mat = scale_matrix(s)
    return Transform(mat)


def ndc_to_cam(aspect, fov):
    fov /= 2
    fov = np.radians(fov)
    tan = np.tan(fov)
    scale = scale_matrix([2 * aspect * tan, 2 * tan, 1])
    translate = translate_matrix([-1 * aspect * tan, -1 * tan, 0])
    t = compose(translate, scale)
    return t


class Camera:
    def __init__(self, resx, resy, fov, seed=1):
        self.resx = resx
        self.resy = resy
        self.fov = fov
        self._build_raster_to_camera()
        self.seed = seed

    def _build_raster_to_camera(self):
        self.r_ndc = raster_to_ndc(self.resx, self.resy)
        self.ndc_cam = ndc_to_cam(self.resx / self.resy, self.fov)
        self.r_cam = compose(self.ndc_cam.mat, self.r_ndc.mat)

    def get_cam(self, x, y, z=1):
        v = np.array([x, y, z])
        return self.r_cam.transform(v)

    def get_raster(self, x, y, z=1):
        v = np.array([x, y, z])
        return self.r_cam.inv_transform(v)

    def get_sample(self):
        (x, y), self.seed = sobol_seq.i4_sobol(2, self.seed)
        #(x, y) = np.random.rand(2)
        x *= self.resx
        y *= self.resy
        u = self.get_cam(x, y)
        return u[0], u[1]


#cam = Camera(100, 100, 45)
#
# for _ in range(100):
#    x = cam.get_sample()
#    y = cam.get_raster(*x)
#
#    print(x)
#    print(y)
#    exit()

#xs = []
#ys = []
#for _ in range(10000):
#    x, y = cam.get_sample()
#    xs.append(x)
#    ys.append(y)
#
#print(np.min(xs), np.max(xs))
#print(np.min(ys), np.max(ys))

