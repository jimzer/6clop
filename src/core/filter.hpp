#ifndef FILTERH
#define FILTERH

#include "core/cyclop.hpp"

namespace filter {

class Filter {
 public:
  Float radius;
  Filter(const Float &r) : radius(r){};
  virtual ~Filter(){};
  virtual Float eval(const Vector2f &v) const = 0;
};

}  // namespace filter

#endif