#include "brute_aggregate.hpp"

#include "sphere.hpp"

namespace hitable {

BruteAggregate::BruteAggregate(const std::vector<Hitable *> &hs)
    : hitables(hs) {}

bool BruteAggregate::hit(const Ray &r, HitRecord *rec) const {
  bool hitIt = false;
  HitRecord tmp;
  for (auto &h : hitables) {
    Sphere *s = (Sphere*)h;
    if (h->hit(r, &tmp)) {
      r.tMax = tmp.t;
      *rec = tmp;
      hitIt = true;
    }
  }
  return hitIt;
}
bool BruteAggregate::hitCheck(const Ray &r) const {
  for (auto &h : hitables) {
    if (h->hitCheck(r)) return true;
  }
  return false;
}
int BruteAggregate::hitablesCount() const { return hitables.size(); }
}  // namespace hitable