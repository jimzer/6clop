import sobol_seq
import numpy as np
import itertools as it
import random as rnd
import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle
from tqdm import tqdm
from multiprocessing import Process, Queue
import time



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
        self.radiance[y][x] += radiance
        self.cum_filter_value[y][x] += filter_value
        self.count[y][x] += 1

    def gen(self):
        img = self.radiance / self.cum_filter_value
        return img.astype("uint8")


class Filter:
    def __init__(self, radius):
        self.radius = radius

    def evaluate(self, v):
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
    #a = np.pi/4
    #xx = x * np.cos(a) - y * np.sin(a)
    #yy = x * np.sin(a) + y * np.cos(a)
    #x, y = xx, yy

    #xx = np.cos(x)*np.sin(y)
    #yy = np.cosh(x)/np.sinc(y)
    #x, y = xx, yy

    c1 = np.array([0, 0, 0])
    c2 = np.array([255, 255, 255])

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


class Film:
    def __init__(self, n_pixels_x, n_pixels_y, fil, radius, samples_per_pixel):
        self.n_pixels_x = n_pixels_x
        self.n_pixels_y = n_pixels_y
        self.filter = fil
        self.radius = radius
        self.samples_per_pixel = samples_per_pixel
        pass

    def render(self, f):
        n_samples = self.n_pixels_y * self.n_pixels_y * self.samples_per_pixel
        seq = sobol_seq.i4_sobol_generate(2, n_samples)
        #seq = np.random.rand(n_samples, 2)

        def process(q, q_res):
            img = Image(self.n_pixels_x, self.n_pixels_y)
            while True:
                msg = q.get(block=True)
                if msg is None:
                    q_res.put(img)
                    print('bbbbb')
                    return
                x_ndc, y_ndc = msg
                x_ndc = x_ndc * 2 - 1
                y_ndc = y_ndc * 2 - 1

                radiance = f(x_ndc, y_ndc)

                x_imc, y_imc = x_ndc * self.n_pixels_x, y_ndc * self.n_pixels_y

                minx, maxx = x_imc - self.radius, x_imc + self.radius
                miny, maxy = y_imc - self.radius, y_imc + self.radius
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
                    cc = np.array([x_imc, y_imc])
                    pp = np.array([x + 0.5, y + 0.5])
                    dd = cc - pp
                    coeff = self.filter.evaluate(dd)
                    img.add_sample(coeff * radiance, coeff, x, y)

            return img

        def monitor(q, n_workers, total_tasks):
            bar = tqdm(total=total_tasks)
            current = 0
            while True:
                if q.empty():
                    for _ in range(4):
                        time.sleep(0.5)
                        q.put(None)
                        time.sleep(0.5)
                    return

                new = total_tasks - q.qsize()
                delta = new - current
                bar.update(delta)
                current = current + delta
                time.sleep(0.1)




        n_workers = 4
        q_samples = Queue()
        q_res = Queue()
        for s in tqdm(seq, leave=False):
            q_samples.put(s)

        mt = Process(target=monitor, args=(q_samples, n_workers, len(seq)))
        mt.start()
        workers = [Process(target=process, args=(q_samples, q_res)) for x in range(n_workers)]
        for worker in workers:
            worker.start()
        mt.join()
        #for worker in workers:
        #    worker.join()

        q_res.put(None)
        imgs = list(iter(q_res.get, None))


        img = imgs[0] + imgs[1] + imgs[2] + imgs[3]

        res = img.gen()
        print(img.count.mean())
        plt.imshow(res)
        plt.show()
        plt.imsave("img2.jpg", res)


radius = 1
fil = Filter(radius)
fil.visualize()
film = Film(100, 100, fil, radius, 10)

film.render(checker_board)

