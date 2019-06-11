#ifndef PERSPECTIVECAMERAH
#define PERSPECTIVECAMERAH

#include "core/camera.hpp"
#include "core/cyclop.hpp"
#include "core/transform.hpp"

class Ray;

namespace camera {

class PerspectiveCamera : public Camera {
 public:
  Float fov;
  transform::Transform rasterWorld;
  transform::Transform rasterCam;
  transform::Transform camWorld;

  PerspectiveCamera(const Vector3f &f, const Vector3f &t, const Float &rX,
                    const Float &rY, const Float &fov_);

  Ray generateRay(const CameraSample &s) const;
};

}  // namespace camera

#endif