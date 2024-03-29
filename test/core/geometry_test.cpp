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

TEST(geometry, toRadians) {
  Float d1 = 0;
  Float d2 = 45;
  Float d3 = 90;
  Float d4 = 360;

  Float r1 = toRadians(d1);
  Float r2 = toRadians(d2);
  Float r3 = toRadians(d3);
  Float r4 = toRadians(d4);

  ASSERT_FLOAT_EQ(r1, 0);
  ASSERT_FLOAT_EQ(r2, M_PI_4);
  ASSERT_FLOAT_EQ(r3, M_PI_2);
  ASSERT_FLOAT_EQ(r4, 2 * M_PI);
}

TEST(geometry, toDegrees) {
  Float r1 = 0;
  Float r2 = M_PI_4;
  Float r3 = M_PI_2;
  Float r4 = 2 * M_PI;

  Float d1 = toDegrees(r1);
  Float d2 = toDegrees(r2);
  Float d3 = toDegrees(r3);
  Float d4 = toDegrees(r4);

  ASSERT_EQ(d1, 0);
  ASSERT_EQ(d2, 45);
  ASSERT_EQ(d3, 90);
  ASSERT_EQ(d4, 360);
}

TEST(geometry, Bound2iConstructor) {
  Bound2i b(Vector2i, Vector2i);

  ASSERT_NO_THROW();
}

TEST(geometry, Bound2iMembers) {
  Vector2i pMin(0, 0);
  Vector2i pMax(10, 10);
  Bound2i b(pMin, pMax);

  ASSERT_EQ(b.pMin, pMin);
  ASSERT_EQ(b.pMax, pMax);
}

TEST(geometry, Bound2iIterator) {
  Vector2i pMin(0, 0);
  Vector2i pMax(4, 2);
  Bound2i b(pMin, pMax);

  int i = 0;
  for (const Vector2i p : b) {
    int spreadX = b.pMax.x() - b.pMin.x() + 1;
    int row = i / spreadX + b.pMin.y();
    int col = i % spreadX + b.pMin.x();
    Vector2i r(col, row);
    ASSERT_EQ(p, r);
    i++;
  }
}