#ifndef PERSPECTIVECAMERAH
#define PERSPECTIVECAMERAH

#include "core/camera.hpp"
#include "core/cyclop.hpp"
#include "core/transform.hpp"

class Ray;

namespace film {
class Film;
}

namespace camera {

class PerspectiveCamera : public Camera {
 public:
  Float fov;
  transform::Transform rasterWorld;
  transform::Transform rasterCam;
  transform::Transform camWorld;

  PerspectiveCamera(film::Film *fi, const Vector3f &f, const Vector3f &t,
                    const Float &fov_);

  Ray generateRay(const CameraSample &s) const;
};

}  // namespace camera

#endif