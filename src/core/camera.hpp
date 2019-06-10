#ifndef CAMERAH
#define CAMERAH

#include "core/cyclop.hpp"
#include "transform.hpp"

class Ray;

namespace camera {
struct CameraSample {
  Vector3f ndcSample;
  Vector3f lensSample;
};

class Camera {
 public:
  Float resX;
  Float resY;
  Vector3f from;
  Vector3f to;
  transform::Transform camWorld;

  Camera(const Vector3f &f, const Vector3f &t, const Float &rX,
         const Float &rY);

  virtual Ray genRay(const CameraSample &s) const;
};

}  // namespace camera

#endif