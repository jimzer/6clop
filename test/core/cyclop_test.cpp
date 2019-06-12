#include "core/cyclop.hpp"
#include "gtest/gtest.h"

TEST(cyclop, solveQuadraticNoSol) {
  Float a = 2;
  Float b = 2;
  Float c = 2;
  Float t0, t1;
  bool r1 = solveQuadratic(a, b, c, &t0, &t1);
  ASSERT_EQ(r1, false);
}

TEST(cyclop, solveQuadraticOneSol) {
  Float a = 1;
  Float b = -8;
  Float c = 16;
  Float t0, t1;
  bool r1 = solveQuadratic(a, b, c, &t0, &t1);
  ASSERT_EQ(r1, true);
  ASSERT_EQ(t0, t1);
  ASSERT_EQ(t0, 4);
}

TEST(cyclop, solveQuadraticTwoSol) {
  Float a = 3;
  Float b = -11;
  Float c = -4;
  Float t0, t1;
  bool r1 = solveQuadratic(a, b, c, &t0, &t1);
  ASSERT_EQ(r1, true);
  ASSERT_LE(t0, t1);
  ASSERT_FLOAT_EQ(t0, -0.3333333);
  ASSERT_EQ(t1, 4);
}