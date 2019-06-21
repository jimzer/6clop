#ifndef HITABLEH
#define HITABLEH

#include "core/cyclop.hpp"
#include "core/transform.hpp"

class Ray;

namespace hitable {
struct HitRecord {
  Vector3f p;
  Vector3f n;
};

class Hitable {
 public:

  Hitable(){};
  virtual ~Hitable(){};

  virtual bool hit(const Ray &r, HitRecord *rec) const = 0;
  virtual bool hitCheck(const Ray &r) const = 0;
};

}  // namespace hitable

#endif