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
  BoxFilter filter(1);
  Film film("test", Vector2i(1000, 500), &filter);
  Vector3f from(10, 10, 10);
  Vector3f to(0, 0, 0);
  PerspectiveCamera cam(&film, from, to, 90);
  NaiveSampler ns(7);
  HitIntegrator hi(&ns, &cam, 1);

  ASSERT_NO_THROW();
}

TEST(HitIntegrator, render) {
  BoxFilter filter(1);
  Film film("hit-integrator-render-test.ppm", Vector2i(200, 150), &filter);
  Vector3f from(10, 10, 10);
  Vector3f to(2, 0, 0);
  PerspectiveCamera cam(&film, from, to, 25);
  ConstSampler cs(7, 0);
  NaiveSampler ns(7);
  HitIntegrator hi(&ns, &cam, 4);

  Sphere s(Transform(), 2);
  Scene scene(&s);

  hi.render(scene);

  ASSERT_NO_THROW();
}