#include "hitables/sphere.hpp"
#include "core/cyclop.hpp"
#include "core/ray.hpp"
#include "core/transform.hpp"
#include "gtest/gtest.h"

using namespace hitable;
using namespace transform;

TEST(sphere, constructor) {
  Vector3f vt(10, 10, 10);
  Transform t = translateTransform(vt);
  Sphere s(t, 2);
  Vector3f center(0, 0, 0);
  Vector3f p1(1, 1, 1);
  Vector3f w1(10, 0, 0);

  Vector3f r1 = s.objWorld(center, POINT);
  Vector3f r2 = s.objWorld(p1, POINT);
  Vector3f r3 = s.worldObj(w1, POINT);

  ASSERT_EQ(r1, Vector3f(10, 10, 10));
  ASSERT_EQ(r2, Vector3f(11, 11, 11));
  ASSERT_EQ(r3, Vector3f(0, -10, -10));

  ASSERT_EQ(0, 0);
}

TEST(sphere, intersectNoTransform) {
  Transform t;
  Sphere s(t, 2);
  Vector3f o(10, 10, 10);
  Vector3f d(-1, -1, -1);
  Ray r(o, d);

  HitRecord hr;
  bool b = s.hit(r, &hr);

  Vector3f r1 = Vector3f(1, 1, 1).normalized().eval() * 2;
  Vector3f r2 = Vector3f(1, 1, 1).normalized();

  ASSERT_EQ(b, true);
  ASSERT_TRUE(hr.p.isApprox(r1));
  ASSERT_TRUE(hr.n.isApprox(r2));
}

TEST(sphere, intersectTransform) {
  Transform t = translateTransform(Vector3f(10, 10, 10));
  Sphere s(t, 4);
  Vector3f o(-10, -10, -10);
  Vector3f d(1, 1, 1);
  Ray r(o, d);

  HitRecord hr;
  bool b = s.hit(r, &hr);

  Vector3f r1 =
      Vector3f(10, 10, 10) - Vector3f(1, 1, 1).normalized().eval() * 4;
  Vector3f r2 = -Vector3f(1, 1, 1).normalized();

  ASSERT_EQ(b, true);
  ASSERT_TRUE(hr.p.isApprox(r1));
  ASSERT_TRUE(hr.n.isApprox(r2));
}

TEST(sphere, intersectNoIntersection) {
  Transform t = translateTransform(Vector3f(10, 10, 10));
  Sphere s(t, 4);
  Vector3f o(0, 0, 0);
  Vector3f d(1, 0, 0);
  Ray r(o, d);

  HitRecord hr;
  bool b = s.hit(r, &hr);

  ASSERT_EQ(b, false);
}

TEST(sphere, hitPIntersection) {
  Transform t = translateTransform(Vector3f(10, 10, 10));
  Sphere s(t, 4);
  Vector3f o(0, 0, 0);
  Vector3f d(1, 1, 1);
  Ray r(o, d);

  bool b = s.hitCheck(r);

  ASSERT_EQ(b, true);
}

TEST(sphere, hitPNoIntersection) {
  Transform t = translateTransform(Vector3f(10, 10, 10));
  Sphere s(t, 4);
  Vector3f o(0, 0, 0);
  Vector3f d(1, 0, 0);
  Ray r(o, d);

  bool b = s.hitCheck(r);

  ASSERT_EQ(b, false);
}

TEST(sphere, area) {
  Transform t;
  Sphere s1(t, 2);
  Sphere s2(t, 6);

  ASSERT_FLOAT_EQ(s1.area(), 4 * M_PI * 2 * 2);
  ASSERT_FLOAT_EQ(s2.area(), 4 * M_PI * 6 * 6);
}