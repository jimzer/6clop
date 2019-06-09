import sobol_seq
import numpy as np
import itertools as it
import random as rnd
import matplotlib.pyplot as plt
import pyformulas as pf
from matplotlib.patches import Rectangle
from tqdm import tqdm
from multiprocessing import Process, Queue
from transforms import Camera
from collections import Counter
import time
import os

from numba import jitclass

class Image:
    def __init__(self, n_pixels_x, n_pixels_y):
        self.radiance = np.zeros((n_pixels_y, n_pixels_x, 3))
        self.cum_filter_value = np.zeros((n_pixels_y, n_pixels_x, 1))
        self.count = np.zeros((n_pixels_y, n_pixels_x, 1))

    def __add__(self, i):
        self.radiance += i.radiance
        self.cum_filter_value += i.cum_filter_value
        self.count += i.count
        return self

    def add_sample(self, radiance, filter_value, x, y):
        self.radiance[y][x] += radiance * filter_value
        self.cum_filter_value[y][x] += filter_value
        self.count[y][x] += 1

    def gen(self):
        c = self.cum_filter_value.copy()
        c[c == 0] = 1
        img = self.radiance / c
        img *= 255
        return img.astype("uint8")

    def save(self, path):
        res = self.gen()
        plt.imsave("{}.jpg".format(path), res)


class Filter:
    def __init__(self, radius):
        self.radius = radius

    def evaluate(self, v):
        # return 1
        return max(
            np.exp(-np.dot(v, v) / 1) - np.exp(-np.dot(self.radius, self.radius) / 1), 0
        )

    def visualize(self):
        w = 100
        x = np.linspace(-5, 5, w)
        y = np.linspace(-5, 5, w)
        img = np.zeros((w, w))
        for i, xx in enumerate(x):
            for j, yy in enumerate(y):
                coeff = self.evaluate(np.array([xx, yy]))
                img[i][j] = coeff
        plt.imshow(img)
        plt.show()


def checker_board(x, y):
    c1 = np.array([0, 0, 0])
    c2 = np.array([1, 1, 1])

    unit_period = 2 * np.pi
    signal_freq = 4
    v1 = np.cos(x * unit_period * signal_freq - np.pi / 2)
    v2 = np.sin(y * unit_period * signal_freq)
    s1, s2 = np.sign(v1) + 0.1, np.sign(v2) + 0.1
    a = s1 * s2
    if a >= 0:
        return c1
    else:
        return c2

def rotated_checker_board(x, y):
    a = 3.14/3
    xx = x * np.cos(a) - y * np.sin(a)
    yy = x * np.sin(a) + y * np.cos(a)
    x, y = xx, yy
    return checker_board(x, y)

def twisted_checker_board(x, y):
    xx = np.exp(x)
    yy = np.log(np.abs(y))
    x, y = xx, yy
    return checker_board(x, y)



def torus(x, y):
    r = np.cos(x)
    g = np.sin(y)
    b = np.sinc(x+y)

    c = np.array([r, g, b])
    c = np.abs(c)
    c = c / np.linalg.norm(c)
    return c


class Film:
    def __init__(self, n_pixels_x, n_pixels_y, fil, radius, samples_per_pixel, fov):
        self.n_pixels_x = n_pixels_x
        self.n_pixels_y = n_pixels_y
        self.filter = fil
        self.fov = fov
        self.radius = radius
        self.samples_per_pixel = samples_per_pixel

    def render(self, f):
        n_samples = self.n_pixels_y * self.n_pixels_y * self.samples_per_pixel

        seed = int.from_bytes(os.urandom(1), "big")
        cam = Camera(self.n_pixels_x, self.n_pixels_y, self.fov)

        def process(ns):
            img = Image(self.n_pixels_x, self.n_pixels_y)
            for i in range(ns):
                x_cam, y_cam = cam.get_sample()

                radiance = f(x_cam, y_cam)

                x_raster, y_raster, _ = cam.get_raster(x_cam, y_cam)

                minx, maxx = x_raster - self.radius, x_raster + self.radius
                miny, maxy = y_raster - self.radius, y_raster + self.radius

                xs = [
                    int(x)
                    for x in np.arange(0.5, self.n_pixels_x, 1)
                    if x < maxx and x >= minx
                ]
                ys = [
                    int(y)
                    for y in np.arange(0.5, self.n_pixels_y, 1)
                    if y < maxy and y >= miny
                ]

                for x, y in it.product(xs, ys):
                    cc = np.array([x_raster, y_raster])
                    pp = np.array([x + 0.5, y + 0.5])
                    dd = cc - pp
                    coeff = self.filter.evaluate(dd)
                    img.add_sample(radiance, coeff, x, y)
            return img

        # fig = plt.figure()
        canvas = np.zeros((500, 500))
        screen = pf.screen(canvas, "Rendering ...")

        img = Image(self.n_pixels_x, self.n_pixels_y)
        cuts = n_samples // 1000
        ns = n_samples // cuts
        for i in tqdm(range(cuts)):
            img += process(ns)
            res = img.gen()
            # plt.imshow(res)
            # fig.canvas.draw()
            # image = np.fromstring(fig.canvas.tostring_rgb(), dtype=np.uint8, sep="")
            # image = image.reshape(fig.canvas.get_width_height()[::-1] + (3,))
            screen.update(res)

        res = img.gen()
        print(img.count.mean())
        plt.imshow(res)
        plt.show()
        img.save("img2")


radius = 1
fil = Filter(radius)
# fil.visualize()
film = Film(200, 200, fil, radius, 4, 45)

#film.render(checker_board)
film.render(twisted_checker_board)

