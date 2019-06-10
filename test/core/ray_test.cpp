#include "core/cyclop.hpp"
#include "core/ray.hpp"
#include "gtest/gtest.h"

TEST(ray, emptyContructor) {
  Ray r;
  ASSERT_EQ(r.o.x(), 0);
  ASSERT_EQ(r.o.y(), 0);
  ASSERT_EQ(r.o.z(), 0);
}

TEST(ray, rayEvaluation) {
  Vector3f o = Vector3f::Zero();
  Vector3f d(1, 0, 0);
  Ray r(o, d);
  Vector3f p = r(7);
  ASSERT_EQ(p.x(), 7);
  ASSERT_EQ(p.y(), 0);
  ASSERT_EQ(p.z(), 0);
}