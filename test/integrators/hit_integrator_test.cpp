#include "integrators/hit_integrator.hpp"
#include "cameras/perspective_camera.hpp"
#include "core/cyclop.hpp"
#include "core/film.hpp"
#include "core/hitable.hpp"
#include "core/ray.hpp"
#include "core/scene.hpp"
#include "core/transform.hpp"
#include "filters/box_filter.hpp"
#include "gtest/gtest.h"
#include "hitables/brute_aggregate.hpp"
#include "hitables/sphere.hpp"
#include "integrators/hit_integrator.hpp"
#include "samplers/const_sampler.hpp"
#include "samplers/naive_sampler.hpp"

using namespace camera;
using namespace film;
using namespace filter;
using namespace integrator;
using namespace sampler;
using namespace hitable;
using namespace transform;

TEST(HitIntegrator, constructor) {
  Vector3f bc(0, 0, 0);
  Vector3f hc(0, 1, 0);
  BoxFilter filter(1);
  Film film("test", Vector2i(1000, 500), &filter);
  Vector3f from(10, 10, 10);
  Vector3f to(0, 0, 0);
  PerspectiveCamera cam(&film, from, to, 90);
  NaiveSampler ns(7);
  HitIntegrator hi(&ns, &cam, 1, bc, hc);

  ASSERT_NO_THROW();
}

TEST(HitIntegrator, render) {
  Vector3f bc(0, 0, 0);
  Vector3f hc(0, 1, 0);
  BoxFilter filter(1);
  Film film("hit-integrator-render-test.ppm", Vector2i(100, 50), &filter);
  Vector3f from(10, 10, 10);
  Vector3f to(2, 0, 0);
  PerspectiveCamera cam(&film, from, to, 25);
  ConstSampler cs(7, 0);
  NaiveSampler ns(7);
  HitIntegrator hi(&ns, &cam, 1, bc, hc);

  Sphere s(Transform(), 2);
  std::vector<Hitable*> hitables = {&s};
  BruteAggregate agg(hitables);
  Scene scene(&agg);

  hi.render(scene);

  ASSERT_NO_THROW();
}

TEST(HitIntegrator, renderMultiSpheres) {
  Vector3f bc(0, 0, 1);
  Vector3f hc(0, 1, 0);
  BoxFilter filter(1);
  Film film("hit-integrator-render-multi-shperes-test.ppm", Vector2i(100, 50),
            &filter);
  Vector3f from(10, 10, 10);
  Vector3f to(0, 0, 0);
  PerspectiveCamera cam(&film, from, to, 90);
  ConstSampler cs(7, 0);
  NaiveSampler ns(7);
  HitIntegrator hi(&ns, &cam, 1, bc, hc);

  Sphere s1(translateTransform(Vector3f(-2, 2, 4)), 2);
  Sphere s2(translateTransform(Vector3f(4, -4, 2)), 4);
  Sphere s3(translateTransform(Vector3f(0, 0, -100)), 100);
  std::vector<Hitable*> hitables = {&s1, &s2, &s3};
  BruteAggregate agg(hitables);
  Scene scene(&agg);

  hi.render(scene);

  ASSERT_NO_THROW();
}