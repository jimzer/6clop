#ifndef CAMERAH
#define CAMERAH

#include "core/cyclop.hpp"
#include "transform.hpp"

class Ray;

namespace camera {
struct CameraSample {
  Vector2f filmSample;
  Vector2f lensSample;
};

class Camera {
 public:
  transform::Transform rasterToWorld;

  Camera(){};
  virtual ~Camera(){};
  virtual Ray generateRay(const CameraSample &s) const = 0;
};

}  // namespace camera

#endif