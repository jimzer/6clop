#include "filters/box_filter.hpp"
#include "core/cyclop.hpp"
#include "gtest/gtest.h"

using namespace filter;

TEST(boxFilter, constructor) {
  BoxFilter bf(7);
  ASSERT_NO_THROW();
}