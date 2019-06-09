#include "geometry.hpp"
#include "core/cyclop.hpp"

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

  Float toRadians(Float &d) {
    ASSERT(d >= 0 && d <= 360, "Angle should be in the range [0, 360]");
    return d * M_PI / 180.0;
  }

  Float toDegrees(Float &r) {
    ASSERT(r >= 0 && r <= 2*M_PI+0.00001, "Angle should be in the range [0, 2PI]");
    return r * 180.0 / M_PI;
  }

}