#include "box_filter.hpp"

namespace filter {

  BoxFilter::BoxFilter(const Float &r) : Filter(r) {};

  Float BoxFilter::eval(const Vector2f &v) const {
    return 1.0;
  }
}