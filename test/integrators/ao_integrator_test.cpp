#include "integrators/ao_integrator.hpp"
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
#include "samplers/const_sampler.hpp"
#include "samplers/naive_sampler.hpp"

using namespace camera;
using namespace film;
using namespace filter;
using namespace integrator;
using namespace sampler;
using namespace hitable;
using namespace transform;

TEST(AOIntegrator, constructor) {
  BoxFilter filter(1);
  Film film("test", Vector2i(1000, 500), &filter);
  Vector3f from(10, 10, 10);
  Vector3f to(0, 0, 0);
  PerspectiveCamera cam(&film, from, to, 90);
  NaiveSampler ns(7);
  AOIntegrator hi(&ns, &cam, 1, 4);

  ASSERT_NO_THROW();
}


TEST(AOIntegrator, renderMultiSpheres) {
  BoxFilter filter(1);
  Film film("ao-integrator-render-multi-shperes-test.ppm", Vector2i(200, 100),
            &filter);
  Vector3f from(0, 2, 4);
  Vector3f to(0, 1, -1);
  PerspectiveCamera cam(&film, from, to, 90);
  ConstSampler cs(7, 0);
  NaiveSampler ns(7);
  AOIntegrator hi(&ns, &cam, 2, 2);

  Sphere s1(translateTransform(Vector3f(0, 4, -6)), 4);
  Sphere s2(translateTransform(Vector3f(0, -100, -4)), 100);
  std::vector<Hitable*> hitables = {&s1, &s2};
  BruteAggregate agg(hitables);
  Scene scene(&agg);

  hi.render(scene);

  ASSERT_NO_THROW();
}