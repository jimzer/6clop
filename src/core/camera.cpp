#include "camera.hpp"
#include "geometry.hpp"
#include "transform.hpp"

namespace camera {

transform::Transform rasterToNdc(const Float &resX, const Float &resY) {
  Vector3f s(1.0 / resX, 1.0 / resY, 1);
  return transform::scaleTransform(s);
}

transform::Transform ndcToCam(const Float &aspect, const Float &fov) {
  ASSERT(fov >= 0 && fov < 180,
         "The FOV angle should be in the range [0, 180] degrees)");
  Float fov2 = fov / 2;
  fov2 = geometry::toRadians(fov2);
  Float tan = std::tan(fov2);
  Vector3f t(-0.5, -0.5, 0);
  Vector3f s(2 * aspect * tan, -2 * tan, 1);
  auto tt = transform::translateTransform(t);
  auto ts = transform::scaleTransform(s);
  auto res = transform::composeTransforms(ts, tt);
  return res;
}

transform::Transform rasterToCam(const Float &resX, const Float &resY,
                                 const Float &fov) {
  transform::Transform rNdc = rasterToNdc(resX, resY);
  transform::Transform ndcCam = ndcToCam(resX / resY, fov);
  return transform::composeTransforms(ndcCam, rNdc);
}

}  // namespace camera