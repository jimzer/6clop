#include "sphere.hpp"

namespace hitable {

Sphere::Sphere(const transform::Transform &t, const Float &r)
    : objWorld(t), worldObj(t.inverse()), radius(r) {}

bool Sphere::hit(const Ray &r, HitRecord *rec) const {
  Ray ro = worldObj(r);
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

  rec->p = objWorld(pHit, POINT);
  rec->n = objWorld(nHit, NORMAL);
  rec->t = tHit;

  return true;
}

bool Sphere::hitCheck(const Ray &r) const {
  Ray ro = worldObj(r);
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

Float Sphere::area() const {
  return 4 * M_PI * radius * radius;
}

}  // namespace hitable