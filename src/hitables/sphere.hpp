#ifndef SPHEREH
#define SPHEREH

#include "core/cyclop.hpp"
#include "core/hitable.hpp"
#include "core/transform.hpp"

namespace hitable {

class Sphere : public Hitable {
 public:
  Float radius;

  Sphere(const transform::Transform &t, const Float &r);

  bool hit(const Ray &r, HitRecord *rec) const;
  bool hitP(const Ray &r) const;
};

}  // namespace hitable

#endif