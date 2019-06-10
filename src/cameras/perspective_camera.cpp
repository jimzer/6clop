#include "perspective_camera.hpp"

namespace camera {
PerspectiveCamera::PerspectiveCamera(const Vector3f &f, const Vector3f &t,
                                     const Float &rX, const Float &rY,
                                     const Float &fov_)
    : Camera(f, t, rX, rY) {
  fov = fov_;
}
}  // namespace camera