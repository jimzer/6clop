#ifndef RAYH
#define RAYH

#include "core/cyclop.hpp"

class Medium;

class Ray {
 public:
  Vector3f o;
  Vector3f d;
  mutable Float tMax;
  Float time;
  const Medium *medium;

  Ray();
  Ray(const Vector3f &o, const Vector3f &d, Float tMax = Infinity,
           Float time = 0.f, const Medium *medium = nullptr);
  Vector3f operator()(Float t) const;
  bool HasNaNs() const;
  friend std::ostream& operator<<(std::ostream& os, const Ray &r);

};

#endif