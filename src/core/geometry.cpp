#include "geometry.hpp"

namespace geometry {
  Vector4f toHomog(const Vector3f &v, Geomtype g) {
    Vector4f a;
    if (g == POINT) {
      a(3) = 1;
    }
    a.head(3) = v;
    return a;
  }

  Vector3f toRegular(const Vector4f &v) {
    return v.head(3);
  }
}