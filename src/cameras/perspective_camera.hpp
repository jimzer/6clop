#ifndef PERSPECTIVECAMERAH
#define PERSPECTIVECAMERAH

#include "core/camera.hpp"
#include "core/cyclop.hpp"

class Ray;

namespace camera {

class PerspectiveCamera : public Camera {
 public:
  Float fov;
  PerspectiveCamera(const Vector3f &f, const Vector3f &t, const Float &rX,
                    const Float &rY, const Float &fov_);

  Ray genRay(const CameraSample &s) const;
};

}  // namespace camera

#endif