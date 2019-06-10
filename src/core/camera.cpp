#include "camera.hpp"
#include "geometry.hpp"

namespace camera {

Camera::Camera(const Vector3f &f, const Vector3f &t, const Float &rX,
               const Float &rY) {
  resX = rX;
  resX = rY;
  from = f;
  to = t;
  camWorld = transform::camToWorld(from, to);
}


}  // namespace camera