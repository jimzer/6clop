import sobol_seq
import numpy as np
import itertools as it
import random as rnd
import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle
from tqdm import tqdm


def comparison():
    n_samples = 200
    s = 5

    seq = sobol_seq.i4_sobol_generate(2, n_samples)
    x, y = seq[:, 0], seq[:, 1]

    seq2 = np.random.rand(n_samples, 2)
    xx, yy = seq2[:, 0], seq[:, 1]

    fig, axs = plt.subplots(1, 2, figsize=(10, 10))

    for ax in axs.ravel():
        ax.set_xlim(-0.1, 1.1)
        ax.set_ylim(-0.1, 1.1)
        ax.set_xlabel("x")
        ax.set_ylabel("y")
        ax.add_patch(
            Rectangle((0, 0), 1, 1, linewidth=1, edgecolor="r", facecolor="none")
        )
        ax.axis("square")

    axs[0].scatter(x, y, s=s)
    axs[1].scatter(xx, yy, s=s)

    draw_pixels(axs, 10)


def different_sapce(n_pixels, n_samples_per_pixel):
    n_samples = n_pixels * n_samples_per_pixel
    s = 5

    seq = sobol_seq.i4_sobol_generate(2, n_samples)
    x_NDC, y_NDC = seq[:, 0], seq[:, 1]

    x_IMC, y_IMC = x_NDC * n_pixels, y_NDC * n_pixels

    fig, axs = plt.subplots(1, 2, figsize=(10, 10))
    for ax in axs.ravel():
        ax.set_xlabel("x")
        ax.set_ylabel("y")
        ax.axis("square")

    ndc_axis = axs[0]
    imc_axis = axs[1]

    ndc_axis.set_xlim(-0.1, 1.1)
    ndc_axis.set_ylim(-0.1, 1.1)
    ndc_axis.add_patch(
        Rectangle((0, 0), 1, 1, linewidth=1, edgecolor="r", facecolor="none")
    )
    ndc_axis.scatter(x_NDC, y_NDC, s=s)

    imc_axis.set_xlim(-0.1 * n_pixels, 1.1 * n_pixels)
    imc_axis.set_ylim(-0.1 * n_pixels, 1.1 * n_pixels)
    imc_axis.add_patch(
        Rectangle(
            (0, 0),
            1 * n_pixels,
            1 * n_pixels,
            linewidth=1,
            edgecolor="r",
            facecolor="none",
        )
    )
    imc_axis.scatter(x_IMC, y_IMC, s=s)
    filter_raidius_NDC = 4 / 100
    filter_raidius_IMC = filter_raidius_NDC * n_pixels
    for idx_x in range(n_pixels):
        for idx_y in range(n_pixels):
            x = idx_x + 0.5
            y = idx_y + 0.5
            imc_axis.scatter(x=x, y=y, c="r", s=10)
            imc_axis.scatter(x=x, y=y, c="r", s=10)
            imc_axis.add_patch(
                Rectangle(
                    (x - filter_raidius_IMC, y - filter_raidius_IMC),
                    filter_raidius_IMC * 2,
                    filter_raidius_IMC * 2,
                    linewidth=1,
                    edgecolor="r",
                    facecolor="none",
                )
            )


# different_sapce(10, 50)
# plt.show()


def checker_board(x, y):
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


def proceduaral_image():
    sampling_freq = 4
    sampling_period = 1 / sampling_freq

    img = np.zeros((sampling_freq, sampling_freq, 3)).astype("uint8")

    for x in range(sampling_freq):
        for y in range(sampling_freq):
            xx = (x + 0.5) / sampling_freq
            yy = (y + 0.5) / sampling_freq
            # xx = xx ** 2
            # yy = yy ** 2

            res = checker_board(x, y)
            img[x, y] = res

    plt.imshow(img)
    plt.show()

#proceduaral_image()
#exit()


class Pixel:
    def __init__(self):
        self.radiance = np.zeros(3)
        self.cum_filter_value = 0
        self.count = 0

    def add_sample(self, radiance, filter_value):
        self.radiance += radiance
        self.cum_filter_value += filter_value
        self.count += 1

    def value(self):
        if self.cum_filter_value > 0:
            return self.radiance / self.cum_filter_value
        else:
            return self.radiance


class Filter:
    def __init__(self, radius):
        self.radius = radius

    def evaluate(self, v):
        return max(
            np.exp(-np.dot(v, v) / 1) - np.exp(-np.dot(self.radius, self.radius) / 1), 0
        )

    # def evaluate(self, v):
    #    return max(0, self.radius[0] - np.abs(v[0])) * max(
    #        (0, self.radius[1] - np.abs(v[1]))
    #    )

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


def test():
    samples_per_pixel = 10
    n_pixels = 200
    n_samples = n_pixels * n_pixels * samples_per_pixel
    n_samples = 100 * 100 * 10
    seq = sobol_seq.i4_sobol_generate(2, n_samples)

    img = np.zeros((n_pixels, n_pixels, 3)).astype("uint8")

    pixels = {}
    for x in range(n_pixels):
        pixels[x] = {}
        for y in range(n_pixels):
            pixels[x][y] = Pixel()

    samples = []
    for x, y in seq:
        xx = int(x * n_pixels)
        yy = int(y * n_pixels)

        res = checker_board(x, y)
        samples.append((x * n_pixels, y * n_pixels, res))


    rad = 2
    f = Filter([rad, rad])
    # f.visualize()
    for c1, c2, res in tqdm(samples, leave=False):
        minx, maxx = c1 - rad, c1 + rad
        miny, maxy = c2 - rad, c2 + rad

        xs = [x for x in np.arange(0.5, n_pixels, 1) if x < maxx and x >= minx]
        ys = [y for y in np.arange(0.5, n_pixels, 1) if y < maxy and y >= miny]

        for x, y in it.product(xs, ys):
            cc = np.array([c1, c2])
            pp = np.array([x + 0.5, y + 0.5])
            dd = cc - pp
            coeff = f.evaluate(dd)
            pixels[int(x)][int(y)].add_sample(res * coeff, coeff)

    a = []
    for x in range(n_pixels):
        for y in range(n_pixels):
            count = pixels[x][y].count
            a.append(count)
            img[x][y] = pixels[x][y].value()

    print(np.mean(a))

    # exit()
    plt.imshow(img)
    plt.show()


test()
