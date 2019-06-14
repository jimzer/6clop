#include "samplers/naive_sampler.hpp"
#include "core/cyclop.hpp"
#include "gtest/gtest.h"

using namespace sampler;

TEST(naiveSamppler, constructor) {
  NaiveSampler ns(7);
  ASSERT_NO_THROW();
}

TEST(naiveSamppler, sample1D) {
  NaiveSampler ns(7);
  Float s = ns.get1D();
  ASSERT_LT(s, 1);
  ASSERT_GT(s, 0);
}

TEST(naiveSamppler, sample2D) {
  NaiveSampler ns(7);
  Vector2f p = ns.get2D();
  ASSERT_LT(p.x(), 1);
  ASSERT_GT(p.x(), 0);
  ASSERT_LT(p.y(), 1);
  ASSERT_GT(p.y(), 0);
}