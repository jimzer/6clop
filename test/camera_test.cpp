#include "core/camera.hpp"
#include "core/transform.hpp"
#include "core/cyclop.hpp"
#include "gtest/gtest.h"

using namespace camera;
using namespace transform;

TEST(camera, rasterToNdc) {
  Vector3f v1(0, 0, 1);
  Vector3f v2(500, 250, 1);
  Vector3f v3(1000, 500, 1);
  Transform t = rasterToNdc(1000, 500);
  Vector3f r1 = t.apply(v1, POINT);
  Vector3f r2 = t.apply(v2, POINT);
  Vector3f r3 = t.apply(v3, POINT);

  ASSERT_EQ(r1, Vector3f(0, 0 ,1));
  ASSERT_EQ(r2, Vector3f(0.5, 0.5 ,1));
  ASSERT_EQ(r3, Vector3f(1, 1 ,1));
}

TEST(camera, ndcToCam) {
  Vector3f v1(0, 0, 1);
  Vector3f v2(1, 1, 1);
  Vector3f v3(0.5, 0.5, 1);
  Transform t = ndcToCam(2, 90);
  Vector3f r1 = t.apply(v1, POINT);
  Vector3f r2 = t.apply(v2, POINT);
  Vector3f r3 = t.apply(v3, POINT);

  ASSERT_EQ(r1, Vector3f(-2, 1 ,1));
  ASSERT_EQ(r2, Vector3f(2, -1 ,1));
  ASSERT_EQ(r3, Vector3f(0, 0 ,1));
}

TEST(camera, rasterToCam) {
  Vector3f v1(0, 0, 1);
  Vector3f v2(1000, 500, 1);
  Vector3f v3(500, 250, 1);
  Transform t = rasterToCam(1000, 500, 90);
  Vector3f r1 = t.apply(v1, POINT);
  Vector3f r2 = t.apply(v2, POINT);
  Vector3f r3 = t.apply(v3, POINT);

  ASSERT_EQ(r1, Vector3f(-2, 1 ,1));
  ASSERT_EQ(r2, Vector3f(2, -1 ,1));
  ASSERT_EQ(r3, Vector3f(0, 0 ,1));
}