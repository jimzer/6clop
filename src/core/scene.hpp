#ifndef SCENEH
#define SCENEH

#include <memory>
#include "core/cyclop.hpp"
#include "core/hitable.hpp"

class Scene {
 public:
  hitable::Hitable* aggregate;

  Scene(hitable::Hitable *agg);
  bool hit(const Ray &r, hitable::HitRecord *rec) const;
  bool hitCheck(const Ray &r) const;
};

#endif