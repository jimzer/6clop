#include "transform.hpp"
#include <Eigen/Dense>
#include "core/geometry.hpp"

namespace transform {

Transform::Transform() {
  mat = Matrix4f::Identity();
}

Transform::Transform(const Matrix4f &m) {
  ASSERT(!mat.array().isNaN().any(), "NaN in transformation matrix");
  mat = m;
}

Vector3f Transform::operator()(const Vector3f &v, const Geomtype &g) const {
  Vector4f resH = geometry::toHomog(v, g);
  resH = mat * resH;
  return geometry::toRegular(resH);
}  // namespace transform

Ray Transform::operator()(const Ray &r) const {
  Vector3f nO = (*this)(r.o, POINT);
  Vector3f nD = (*this)(r.d, VECTOR);
  return Ray(nO, nD, r.tMax, r.time, r.medium);
}

Transform Transform::inverse() const {
  Matrix4f invMat = mat.inverse();
  ASSERT(!invMat.array().isNaN().any(), "NaN in inverted transformation matrix");
  return Transform(invMat);
}

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

Transform basisChange(const Vector3f &x, const Vector3f &y, const Vector3f &z) {
  Matrix4f m = Matrix4f::Identity();
  m.row(0).head(3) = x;
  m.row(1).head(3) = y;
  m.row(2).head(3) = z;
  return Transform(m);
}

Transform rasterToNdc(const Float &resX, const Float &resY) {
  Vector3f s(1.0 / resX, 1.0 / resY, 1);
  return scaleTransform(s);
}

Transform ndcToCam(const Float &aspect, const Float &fov) {
  ASSERT(fov >= 0 && fov < 180,
         "The FOV angle should be in the range [0, 180] degrees)");
  Float fov2 = fov / 2;
  fov2 = geometry::toRadians(fov2);
  Float tan = std::tan(fov2);
  Vector3f t(-0.5, -0.5, 0);
  Vector3f s(2 * aspect * tan, -2 * tan, 1);
  auto tt = translateTransform(t);
  auto ts = scaleTransform(s);
  auto res = composeTransforms(ts, tt);
  return res;
}

Transform rasterToCam(const Float &resX, const Float &resY, const Float &fov) {
  Transform rNdc = rasterToNdc(resX, resY);
  Transform ndcCam = ndcToCam(resX / resY, fov);
  return composeTransforms(ndcCam, rNdc);
}

Transform camToWorld(const Vector3f &from, const Vector3f &to) {
  Vector3f forward = (from - to).normalized();
  Vector3f tmp = Vector3f(0, 1, 0);
  Vector3f right = tmp.cross(forward).normalized();
  Vector3f up = forward.cross(right);

  Transform coordinateChange = basisChange(right, up, forward);
  Transform invCoordinateChange =  coordinateChange.inverse();
  Transform t = translateTransform(from);

  return composeTransforms(t, invCoordinateChange);
}

Transform rasterToWorld(const Float &resX, const Float &resY, const Float &fov,
                        const Vector3f &from, const Vector3f &to) {
  Transform rCam = rasterToCam(resX, resY, fov);
  Transform cWorld = camToWorld(from, to);
  return composeTransforms(cWorld, rCam);
}

}  // namespace transform