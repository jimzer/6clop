#include "core/scene.hpp"
#include "core/cyclop.hpp"
#include "core/ray.hpp"
#include "core/transform.hpp"
#include "gtest/gtest.h"
#include "hitables/brute_aggregate.hpp"
#include "hitables/sphere.hpp"

using namespace hitable;
using namespace transform;

TEST(scene, constructor) {
  Vector3f vt(10, 10, 10);
  Transform t = translateTransform(vt);
  Sphere s(t, 2);
  Vector3f center(0, 0, 0);
  Vector3f p1(1, 1, 1);
  Vector3f w1(10, 0, 0);
  std::vector<Hitable*> hitables = {&s};
  BruteAggregate agg(hitables);
  Scene scene(&agg);

  ASSERT_NO_THROW();
}

TEST(scene, intersectNoTransform) {
  Transform t;
  Sphere s(t, 2);
  Vector3f o(10, 10, 10);
  Vector3f d(-1, -1, -1);
  Ray r(o, d);
  HitRecord hr;
  std::vector<Hitable*> hitables = {&s};
  BruteAggregate agg(hitables);
  Scene scene(&agg);
  bool b = scene.hit(r, &hr);

  Vector3f r1 = Vector3f(1, 1, 1).normalized().eval() * 2;
  Vector3f r2 = Vector3f(1, 1, 1).normalized();

  ASSERT_EQ(b, true);
  ASSERT_TRUE(hr.p.isApprox(r1));
  ASSERT_TRUE(hr.n.isApprox(r2));
}

TEST(scene, intersectTransform) {
  Transform t = translateTransform(Vector3f(10, 10, 10));
  Sphere s(t, 4);
  Vector3f o(-10, -10, -10);
  Vector3f d(1, 1, 1);
  Ray r(o, d);
  std::vector<Hitable*> hitables = {&s};
  BruteAggregate agg(hitables);
  Scene scene(&agg);

  HitRecord hr;
  bool b = scene.hit(r, &hr);

  Vector3f r1 =
      Vector3f(10, 10, 10) - Vector3f(1, 1, 1).normalized().eval() * 4;
  Vector3f r2 = -Vector3f(1, 1, 1).normalized();

  ASSERT_EQ(b, true);
  ASSERT_TRUE(hr.p.isApprox(r1));
  ASSERT_TRUE(hr.n.isApprox(r2));
}

TEST(scene, intersectNoIntersection) {
  Transform t = translateTransform(Vector3f(10, 10, 10));
  Sphere s(t, 4);
  Vector3f o(0, 0, 0);
  Vector3f d(1, 0, 0);
  Ray r(o, d);
  std::vector<Hitable*> hitables = {&s};
  BruteAggregate agg(hitables);
  Scene scene(&agg);

  HitRecord hr;
  bool b = scene.hit(r, &hr);

  ASSERT_EQ(b, false);
}

TEST(scene, hitPIntersection) {
  Transform t = translateTransform(Vector3f(10, 10, 10));
  Sphere s(t, 4);
  Vector3f o(0, 0, 0);
  Vector3f d(1, 1, 1);
  Ray r(o, d);
  std::vector<Hitable*> hitables = {&s};
  BruteAggregate agg(hitables);
  Scene scene(&agg);

  bool b = scene.hitCheck(r);

  ASSERT_EQ(b, true);
}

TEST(scene, hitPNoIntersection) {
  Transform t = translateTransform(Vector3f(10, 10, 10));
  Sphere s(t, 4);
  Vector3f o(0, 0, 0);
  Vector3f d(1, 0, 0);
  Ray r(o, d);
  std::vector<Hitable*> hitables = {&s};
  BruteAggregate agg(hitables);
  Scene scene(&agg);

  bool b = scene.hitCheck(r);

  ASSERT_EQ(b, false);
}