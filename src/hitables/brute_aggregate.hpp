#ifndef BRUTEAGGREGATEH
#define BRUTEAGGREGATEH

#include <memory>
#include "core/cyclop.hpp"
#include "core/hitable.hpp"

namespace hitable {

class BruteAggregate : public Aggregate {
 public:
  std::vector<Hitable*> hitables;

  BruteAggregate(const std::vector<Hitable*> &hs);

  bool hit(const Ray &r, HitRecord *rec) const;
  bool hitCheck(const Ray &r) const;
  int hitablesCount() const;
};

}  // namespace hitable

#endif