#include "transform.hpp"
#include <Eigen/Dense>
#include "core/geometry.hpp"

namespace transform {

Transform::Transform(const Matrix4f &m) {
  mat = m;
  invMat = mat.inverse();
  ASSERT(!invMat.array().isNaN().any(), "NaN in transformation matrix");
}

Vector3f Transform::apply(const Vector3f &v, Geomtype g) {
  Vector4f resH = geometry::toHomog(v, g);
  resH = mat * resH;
  return geometry::toRegular(resH);
}

Vector3f Transform::invApply(const Vector3f &v, Geomtype g) {
  Vector4f resH = geometry::toHomog(v, g);
  resH = invMat * resH;
  return geometry::toRegular(resH);
};

Transform scaleTransform(const Vector3f &s) {
  Matrix4f m = Matrix4f::Identity();
  m(0, 0) = s(0);
  m(1, 1) = s(1);
  m(2, 2) = s(2);
  return Transform(m);
}

Transform translateTransform(const Vector3f &s) {
  Matrix4f m = Matrix4f::Identity();
  m(0, 3) = s(0);
  m(1, 3) = s(1);
  m(2, 3) = s(2);
  return Transform(m);
}

}  // namespace transform