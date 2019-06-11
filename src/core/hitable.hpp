#ifndef HITABLEH
#define HITABLEH

#include "core/cyclop.hpp"
#include "core/transform.hpp"

class Ray;

namespace hitable {
struct HitRecord {
  Vector3f p;
  Vector3f normal;
};

class Hitable {
 public:
  transform::Transform objWorld;

  Hitable(){};
  virtual ~Hitable(){};

  virtual bool hit(const Ray &r, HitRecord &rec) const = 0;
};

}  // namespace hitable

#endif