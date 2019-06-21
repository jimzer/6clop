#include "perspective_camera.hpp"
#include "core/film.hpp"

namespace camera {
PerspectiveCamera::PerspectiveCamera(film::Film *fi, const Vector3f &f,
                                     const Vector3f &t, const Float &fov_) {
  film = fi;
  fov = fov_;
  rasterWorld = transform::rasterToWorld(film->resolution.x(), film->resolution.y(), fov, f, t);
  rasterCam = transform::rasterToCam(film->resolution.x(), film->resolution.y(), fov);
  camWorld = transform::camToWorld(f, t);
}

Ray PerspectiveCamera::generateRay(const CameraSample &cs) const {
  Vector3f o(0, 0, 0);
  Vector3f d = Vector3f(cs.filmSample.x(), cs.filmSample.y(), -1);
  d = rasterCam(d, POINT);
  Ray r = Ray(o, d);
  return camWorld(r);
}

}  // namespace camera