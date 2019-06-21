#include "hitables/brute_aggregate.hpp"
#include "core/cyclop.hpp"
#include "core/ray.hpp"
#include "core/transform.hpp"
#include "gtest/gtest.h"
#include "hitables/sphere.hpp"

using namespace hitable;
using namespace transform;

TEST(BruteAggregate, constructor) {
  Vector3f vt1(10, 10, 10);
  Transform t1 = translateTransform(vt1);
  Sphere s1(t1, 2);
  Vector3f vt2(10, 10, 10);
  Transform t2 = translateTransform(vt2);
  Sphere s2(t2, 4);
  std::vector<Hitable*> hitables = {&s1, &s2};
  BruteAggregate agg(hitables);

  ASSERT_NO_THROW();
}

TEST(BruteAggregate, separatedSphereHitS1) {
  Vector3f vt1(10, 10, 0);
  Transform t1 = translateTransform(vt1);
  Sphere s1(t1, 2);
  Vector3f vt2(-10, 10, 0);
  Transform t2 = translateTransform(vt2);
  Sphere s2(t2, 4);
  std::vector<Hitable*> hitables = {&s1, &s2};
  BruteAggregate agg(hitables);
  Ray r(Vector3f(0, 0, 0), Vector3f(1, 1, 0));

  HitRecord hr;
  bool hitIt = agg.hit(r, &hr);
  Vector3f res = Vector3f(10, 10, 0) - Vector3f(1, 1, 0).normalized() * 2;

  ASSERT_EQ(hitIt, true);
  ASSERT_TRUE(hr.p.isApprox(res));
}

TEST(BruteAggregate, separatedSphereHitS2) {
  Vector3f vt1(10, 10, 0);
  Transform t1 = translateTransform(vt1);
  Sphere s1(t1, 2);
  Vector3f vt2(-10, 10, 0);
  Transform t2 = translateTransform(vt2);
  Sphere s2(t2, 4);
  std::vector<Hitable*> hitables = {&s1, &s2};
  BruteAggregate agg(hitables);
  Ray r(Vector3f(0, 0, 0), Vector3f(-1, 1, 0));

  HitRecord hr;
  bool hitIt = agg.hit(r, &hr);
  Vector3f res = Vector3f(-10, 10, 0) - Vector3f(-1, 1, 0).normalized() * 4;

  ASSERT_EQ(hitIt, true);
  ASSERT_TRUE(hr.p.isApprox(res));
}

TEST(BruteAggregate, overlapHitS1) {
  Vector3f vt1(10, 10, 0);
  Transform t1 = translateTransform(vt1);
  Sphere s1(t1, 2);
  Vector3f vt2(25, 25, 0);
  Transform t2 = translateTransform(vt2);
  Sphere s2(t2, 10);
  std::vector<Hitable*> hitables = {&s2, &s1};
  BruteAggregate agg(hitables);
  Ray r(Vector3f(0, 0, 0), Vector3f(1, 1, 0));

  HitRecord hr;
  bool hitIt = agg.hit(r, &hr);
  Vector3f res = Vector3f(10, 10, 0) - Vector3f(1, 1, 0).normalized() * 2;

  ASSERT_EQ(hitIt, true);
  ASSERT_TRUE(hr.p.isApprox(res));
}

TEST(BruteAggregate, overlapHitS2) {
  Vector3f vt1(10, 10, 0);
  Transform t1 = translateTransform(vt1);
  Sphere s1(t1, 2);
  Vector3f vt2(25, 25, 0);
  Transform t2 = translateTransform(vt2);
  Sphere s2(t2, 10);
  std::vector<Hitable*> hitables = {&s1, &s2};
  BruteAggregate agg(hitables);
  Ray r(Vector3f(0, 0, 0), Vector3f(1.5, 1, 0));

  HitRecord hr;
  bool hitIt = agg.hit(r, &hr);

  ASSERT_EQ(hitIt, true);
  ASSERT_GT(hr.t, 20);
}