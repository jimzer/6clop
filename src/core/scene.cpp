#include "scene.hpp"

Scene::Scene(hitable::Hitable *agg) : aggregate(agg){};

bool Scene::hit(const Ray &r, hitable::HitRecord *rec) const {
  return aggregate->hit(r, rec);
}

bool Scene::hitCheck(const Ray &r) const {
  return aggregate->hitCheck(r);
}