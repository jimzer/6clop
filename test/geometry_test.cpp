#include "core/geometry.hpp"
#include "core/cyclop.hpp"
#include "gtest/gtest.h"

using namespace geometry;

TEST(geometry, toHomog) {
  Vector3f v(1, 2, 3);
  Vector4f vpH = toHomog(v, POINT);
  Vector4f vvH = toHomog(v, VECTOR);

  ASSERT_EQ(vpH(0), 1);
  ASSERT_EQ(vpH(1), 2);
  ASSERT_EQ(vpH(2), 3);
  ASSERT_EQ(vpH(3), 1);

  ASSERT_EQ(vvH(0), 1);
  ASSERT_EQ(vvH(1), 2);
  ASSERT_EQ(vvH(2), 3);
  ASSERT_EQ(vvH(3), 0);
}
