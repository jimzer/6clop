#include "perspective_camera.hpp"
#include "core/ray.hpp"

namespace camera {
PerspectiveCamera::PerspectiveCamera(const Vector3f &f, const Vector3f &t,
                                     const Float &rX, const Float &rY,
                                     const Float &fov_) {
  fov = fov_;
  rasterWorld = transform::rasterToWorld(rX, rY, fov, f, t);
  rasterCam = transform::rasterToCam(rX, rY, fov);
  camWorld = transform::camToWorld(f, t);
}

Ray PerspectiveCamera::generateRay(const CameraSample &cs) const {
  Vector3f o(0, 0, 0);
  Vector3f d = Vector3f(cs.filmSample.x(), cs.filmSample.y(), -1);
  d = rasterCam.apply(d, POINT);
  Ray r = Ray(o, d);
  return camWorld.apply(r);
}

}  // namespace camera