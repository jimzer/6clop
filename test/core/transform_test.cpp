#include "core/transform.hpp"
#include "core/cyclop.hpp"
#include "gtest/gtest.h"

using namespace transform;

TEST(Transform, constructor) {
  Matrix4f a = Matrix4f::Identity();
  Transform t(a);
}

TEST(Transform, scaleTransform) {
  Vector3f v(1, 0, 2);
  Vector3f v1(1, 2, 3);
  Transform t1 = scaleTransform(v1);
  Transform invt1 = t1.inverse();

  Vector3f r1 = t1(v, POINT);
  Vector3f ri1 = invt1(r1, POINT);

  Vector3f r2 = t1(v, VECTOR);
  Vector3f ri2 = invt1(r2, VECTOR);

  ASSERT_EQ(t1.mat(0, 0), 1);
  ASSERT_EQ(t1.mat(1, 1), 2);
  ASSERT_EQ(t1.mat(2, 2), 3);
  ASSERT_EQ(t1.mat(3, 3), 1);

  ASSERT_EQ(r1(0), 1);
  ASSERT_EQ(r1(1), 0);
  ASSERT_EQ(r1(2), 6);
  ASSERT_EQ(ri1, v);

  ASSERT_EQ(r2(0), 1);
  ASSERT_EQ(r2(1), 0);
  ASSERT_EQ(r2(2), 6);
  ASSERT_EQ(ri2, v);
}

TEST(Transform, translateTransform) {
  Vector3f v(1, 0, 2);
  Vector3f v1(1, 2, 3);
  Transform t1 = translateTransform(v1);
  Transform invt1 = t1.inverse();

  Vector3f r1 = t1(v, POINT);
  Vector3f ri1 = invt1(r1, POINT);

  Vector3f r2 = t1(v, VECTOR);
  Vector3f ri2 = invt1(r2, VECTOR);

  ASSERT_EQ(t1.mat(0, 0), 1);
  ASSERT_EQ(t1.mat(1, 1), 1);
  ASSERT_EQ(t1.mat(2, 2), 1);
  ASSERT_EQ(t1.mat(3, 3), 1);
  ASSERT_EQ(t1.mat(0, 3), 1);
  ASSERT_EQ(t1.mat(1, 3), 2);
  ASSERT_EQ(t1.mat(2, 3), 3);

  ASSERT_EQ(r1(0), 2);
  ASSERT_EQ(r1(1), 2);
  ASSERT_EQ(r1(2), 5);
  ASSERT_EQ(ri1, v);

  ASSERT_EQ(r2, v);
  ASSERT_EQ(ri2, v);
}

TEST(Transform, composeTransforms) {
  Vector3f v(1, 1, 1);
  Vector3f vs1(2, 2, 2);
  Vector3f vt(2, 4, 8);
  Vector3f vs2(1, 1, 4);
  Transform ts1 = scaleTransform(vs1);
  Transform tt = translateTransform(vt);
  Transform ts2 = scaleTransform(vs2);

  Transform t1 = composeTransforms(ts1, tt);
  Transform invt1 = t1.inverse();
  Transform t2 = composeTransforms(ts1, tt, ts2);
  Transform invt2 = t2.inverse();

  Vector3f r1 = t1(v, POINT);
  Vector3f rr1 = invt1(r1, POINT);

  Vector3f r2 = t2(v, POINT);
  Vector3f rr2 = invt2(r2, POINT);

  ASSERT_EQ(r1, Vector3f(6, 10, 18));
  ASSERT_EQ(rr1, v);

  ASSERT_EQ(r2, Vector3f(6, 10, 24));
  ASSERT_EQ(rr2, v);
}

TEST(Transform, rasterToNdc) {
  Vector3f v1(0, 0, -1);
  Vector3f v2(500, 250, -1);
  Vector3f v3(1000, 500, -1);
  Transform t = rasterToNdc(1000, 500);
  Vector3f r1 = t(v1, POINT);
  Vector3f r2 = t(v2, POINT);
  Vector3f r3 = t(v3, POINT);

  ASSERT_EQ(r1, Vector3f(0, 0, -1));
  ASSERT_EQ(r2, Vector3f(0.5, 0.5, -1));
  ASSERT_EQ(r3, Vector3f(1, 1, -1));
}

TEST(Transform, ndcToCam) {
  Vector3f v1(0, 0, -1);
  Vector3f v2(1, 1, -1);
  Vector3f v3(0.5, 0.5, -1);
  Transform t = ndcToCam(2, 90);
  Vector3f r1 = t(v1, POINT);
  Vector3f r2 = t(v2, POINT);
  Vector3f r3 = t(v3, POINT);

  ASSERT_EQ(r1, Vector3f(-2, 1, -1));
  ASSERT_EQ(r2, Vector3f(2, -1, -1));
  ASSERT_EQ(r3, Vector3f(0, 0, -1));
}

TEST(Transform, rasterToCam) {
  Vector3f v1(0, 0, -1);
  Vector3f v2(1000, 500, -1);
  Vector3f v3(500, 250, -1);
  Transform t = rasterToCam(1000, 500, 90);
  Vector3f r1 = t(v1, POINT);
  Vector3f r2 = t(v2, POINT);
  Vector3f r3 = t(v3, POINT);

  ASSERT_EQ(r1, Vector3f(-2, 1, -1));
  ASSERT_EQ(r2, Vector3f(2, -1, -1));
  ASSERT_EQ(r3, Vector3f(0, 0, -1));
}

TEST(Transform, worldToCam) {
  Vector3f from(10, 10, 10);
  Vector3f to(0, 0, 0);
  Transform t = camToWorld(from ,to);

  Vector3f v(0, 0, -1);

  Vector3f delta = Vector3f(-1, -1, -1).normalized();
  Vector3f r = t(v, POINT);

  ASSERT_EQ(r, from + delta);
}

TEST(Transform, rasterToWorld) {
  Vector3f from(10, 10, 10);
  Vector3f to(0, 0, 0);
  Transform t = rasterToWorld(1000, 500, 90, from, to);

  Vector3f v(500, 250, -1);
  Vector3f r = t(v, POINT);

  Vector3f delta = Vector3f(-1, -1, -1).normalized();

  ASSERT_EQ(r, from + delta);
}

TEST(Transform, coordinateSytem) {
  Vector3f n(20, 10, 10);
  Transform cs = coordinateSystem(n);
  Vector3f x = cs.mat.col(0).head(3);
  Vector3f y = cs.mat.col(1).head(3);
  Vector3f z = cs.mat.col(2).head(3);

  ASSERT_FLOAT_EQ(x.dot(y), 0);
  ASSERT_FLOAT_EQ(x.dot(y), 0);
  ASSERT_FLOAT_EQ(y.dot(z), 0);
  ASSERT_FLOAT_EQ(x.norm(), 1);
  ASSERT_FLOAT_EQ(y.norm(), 1);
  ASSERT_FLOAT_EQ(z.norm(), 1);

}