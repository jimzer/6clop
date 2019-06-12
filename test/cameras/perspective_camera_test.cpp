#include "cameras/perspective_camera.hpp"
#include "core/cyclop.hpp"
#include "core/ray.hpp"
#include "gtest/gtest.h"

using namespace camera;

TEST(perspectiveCamera, generateRay) {
  Vector3f from(10, 10, 10);
  Vector3f to(0, 0, 0);
  PerspectiveCamera cam(from, to, 1000, 500, 90);
  CameraSample cs;
  cs.filmSample = Vector2f(500, 250);
  Ray r = cam.generateRay(cs);
  Vector3f delta = Vector3f(-1, -1, -1).normalized();

  Vector3f rEval2 = r.o + 2 * delta;

  ASSERT_EQ(r.o, from);
  ASSERT_EQ(r.d, delta);
  ASSERT_EQ(r(2), rEval2);
}