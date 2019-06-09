#ifndef TRANSFORMH
#define TRANSFORMH

#include "core/cyclop.hpp"

namespace transform {

class Transform {
 private:
 public:
  Matrix4f mat;
  Matrix4f invMat;

  Transform(const Matrix4f &m);

  Vector3f apply(const Vector3f &v, Geomtype g);
  Vector3f invApply(const Vector3f &v, Geomtype g);
};

Transform scaleTransform(const Vector3f &s);
Transform translateTransform(const Vector3f &s);

template <typename... Args>
Transform composeTransforms(Args &&... args) {
  Matrix4f m = Matrix4f::Identity();
  for (auto &&t : {args...}) {
    m *= t.mat;
  }
  return Transform(m);
}

Transform rasterToNdc(const Float &resX, const Float &resY);
Transform ndcToCam(const Float &aspect, const Float &fov);
Transform rasterToCam(const Float &resX, const Float &resY, const Float &fov);

}  // namespace transform

#endif