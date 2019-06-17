#include "integrators/hit_integrator.hpp"
#include "cameras/perspective_camera.hpp"
#include "core/cyclop.hpp"
#include "core/film.hpp"
#include "core/ray.hpp"
#include "filters/box_filter.hpp"
#include "gtest/gtest.h"
#include "integrators/hit_integrator.hpp"
#include "samplers/naive_sampler.hpp"

using namespace camera;
using namespace film;
using namespace filter;
using namespace integrator;
using namespace sampler;

TEST(HitIntegrator, constructor) {
  BoxFilter filter(1);
  Film film("test", Vector2i(1000, 500), &filter);
  Vector3f from(10, 10, 10);
  Vector3f to(0, 0, 0);
  PerspectiveCamera cam(&film, from, to, 90);

  NaiveSampler ns(7);

  HitIntegrator hi(&ns, &cam);
}