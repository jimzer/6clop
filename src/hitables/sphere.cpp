#include "sphere.hpp"

namespace hitable {

Sphere::Sphere(const transform::Transform &t, const Float &r) {
  objWorld = t;
  radius = r;
}

bool Sphere::hit(const Ray &r, HitRecord *rec) const {
  Ray ro = objWorld.invApply(r);
  Float a = ro.d.dot(ro.d);
  Float b = 2 * ro.d.dot(ro.o);
  Float c = ro.o.dot(ro.o) - radius * radius;

  Float t0, t1;
  if (!solveQuadratic(a, b, c, &t0, &t1)) {
    return false;
  }

  if (t0 > ro.tMax || t1 < 0.0001) {
    return false;
  }

  Float tHit = t0;
  if (t0 < 0.0001) {
    tHit = t1;
    if (tHit > ro.tMax) {
      return false;
    }
  }

  Vector3f pHit = ro(tHit);
  Vector3f nHit = pHit.normalized();

  rec->p = objWorld.apply(pHit, POINT);
  rec->n = objWorld.apply(nHit, NORMAL);

  return true;
}

bool Sphere::hitP(const Ray &r) const {
  Ray ro = objWorld.invApply(r);
  Float a = ro.d.dot(ro.d);
  Float b = 2 * ro.d.dot(ro.o);
  Float c = ro.o.dot(ro.o) - radius * radius;

  Float t0, t1;
  if (!solveQuadratic(a, b, c, &t0, &t1)) {
    return false;
  }

  if (t0 > ro.tMax || t1 < 0.0001) {
    return false;
  }

  Float tHit = t0;
  if (t0 < 0.0001) {
    tHit = t1;
    if (tHit > ro.tMax) {
      return false;
    }
  }

  return true;
}

}  // namespace hitable