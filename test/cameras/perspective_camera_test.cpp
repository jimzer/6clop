#include "cameras/perspective_camera.hpp"
#include "core/cyclop.hpp"
#include "core/film.hpp"
#include "filters/box_filter.hpp"
#include "core/ray.hpp"
#include "gtest/gtest.h"

using namespace camera;
using namespace film;
using namespace filter;

TEST(perspectiveCamera, generateRay) {
  BoxFilter filter(1);
  Film film("test", Vector2i(1000, 500), &filter);
  Vector3f from(10, 10, 10);
  Vector3f to(0, 0, 0);
  PerspectiveCamera cam(&film, from, to, 90);
  CameraSample cs;
  cs.filmSample = Vector2f(500, 250);
  Ray r = cam.generateRay(cs);
  Vector3f delta = Vector3f(-1, -1, -1).normalized();

  Vector3f rEval2 = r.o + 2 * delta;

  ASSERT_EQ(r.o, from);
  ASSERT_EQ(r.d, delta);
  ASSERT_EQ(r(2), rEval2);
}