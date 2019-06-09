#ifndef GEOMTRYH
#define GEOMTRYH

#include "core/cyclop.hpp"

namespace geometry {
  Vector4f toHomog(const Vector3f &v, Geomtype g);
  Vector3f toRegular(const Vector4f &v);
  Float toRadians(Float &d);
  Float toDegrees(Float &r);
}


#endif