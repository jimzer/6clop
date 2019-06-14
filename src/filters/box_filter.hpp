#ifndef BOXFILTERH
#define BOXFILTERH

#include "core/cyclop.hpp"
#include "core/filter.hpp"

namespace filter {

class BoxFilter: public Filter {
 public:
  BoxFilter(const Float &r);
  Float eval(const Vector2f &v) const;
};

}  // namespace filter

#endif