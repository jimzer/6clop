
#include "core/film.hpp"
#include "core/cyclop.hpp"
#include "filters/box_filter.hpp"
#include "gtest/gtest.h"

using namespace film;
using namespace filter;

TEST(film, constructor) {
  Vector2i resolution(100, 50);
  BoxFilter filter(2);
  Film film(resolution, &filter);
  ASSERT_NO_THROW();
}

TEST(film, getContribPixels) {
  Vector2i resolution(100, 50);
  BoxFilter filter(1);
  Film film(resolution, &filter);

  Vector2f pFilm(3.1, 3.6);
  Vector2i rMin, rMax;
  getContribPixels(pFilm, filter.radius, &rMin, &rMax);

  Vector2f r1 = Vector2f(0.5, 0.5) + rMin.cast<Float>();
  Vector2f r2 = Vector2f(0.5, 0.5) + rMax.cast<Float>();
  Vector2f e1 = pFilm - Vector2f(filter.radius, filter.radius);
  Vector2f e2 = pFilm + Vector2f(filter.radius, filter.radius);

  ASSERT_GE(r1.x(), e1.x());
  ASSERT_GE(r1.y(), e1.y());
  ASSERT_LE(r2.x(), e2.x());
  ASSERT_LE(r2.y(), e2.y());
}

TEST(film, addOneSample) {
  Vector2i resolution(100, 50);
  BoxFilter filter(1);
  Film film(resolution, &filter);

  Vector2f pFilm(3.1, 3.6);

  Vector3f radiance1(10, 10, 10);

  film.addSample(pFilm, radiance1, 10);

  Pixel *n1 = film.getPixel(Vector2i(1, 3));
  Pixel *p1 = film.getPixel(Vector2i(2, 3));
  Pixel *p2 = film.getPixel(Vector2i(2, 3));
  Pixel *p3 = film.getPixel(Vector2i(3, 4));
  Pixel *p4 = film.getPixel(Vector2i(3, 4));
  Pixel *n2 = film.getPixel(Vector2i(4, 4));

  ASSERT_EQ(p1->contribSum, radiance1);
  ASSERT_EQ(p1->filterWeightSum, 10);
  ASSERT_EQ(p2->contribSum, radiance1);
  ASSERT_EQ(p2->filterWeightSum, 10);
  ASSERT_EQ(p3->contribSum, radiance1);
  ASSERT_EQ(p3->filterWeightSum, 10);
  ASSERT_EQ(p4->contribSum, radiance1);
  ASSERT_EQ(p4->filterWeightSum, 10);
  ASSERT_EQ(n1->contribSum, Vector3f());
  ASSERT_EQ(n1->filterWeightSum, 0);
  ASSERT_EQ(n2->contribSum, Vector3f());
  ASSERT_EQ(n2->filterWeightSum, 0);
}

TEST(film, addTwoSamples) {
  Vector2i resolution(100, 50);
  BoxFilter filter(1);
  Film film(resolution, &filter);

  Vector2f pFilm1(3.1, 3.6);
  Float filterWeight1 = 10;
  Vector3f radiance1(10, 10, 10);
  Vector2f pFilm2(4.1, 4.6);
  Float filterWeight2 = 2;
  Vector3f radiance2(5, 10, 15);

  film.addSample(pFilm1, radiance1, filterWeight1);
  film.addSample(pFilm2, radiance2, filterWeight2);

  Pixel *n1 = film.getPixel(Vector2i(1, 3));
  Pixel *p1 = film.getPixel(Vector2i(2, 3));
  Pixel *p2 = film.getPixel(Vector2i(2, 3));
  Pixel *p3 = film.getPixel(Vector2i(3, 4));
  Pixel *p4 = film.getPixel(Vector2i(3, 4));
  Pixel *n2 = film.getPixel(Vector2i(4, 4));

  ASSERT_EQ(p1->contribSum, radiance1);
  ASSERT_EQ(p1->filterWeightSum, 10);
  ASSERT_EQ(p2->contribSum, radiance1);
  ASSERT_EQ(p2->filterWeightSum, 10);
  ASSERT_EQ(p3->contribSum, radiance1);
  ASSERT_EQ(p3->filterWeightSum, 10);
  ASSERT_EQ(p4->contribSum, radiance1);
  ASSERT_EQ(p4->filterWeightSum, 10);
  ASSERT_EQ(n1->contribSum, Vector3f());
  ASSERT_EQ(n1->filterWeightSum, 0);
  ASSERT_EQ(n2->contribSum, Vector3f());
  ASSERT_EQ(n2->filterWeightSum, 0);
}