#include "ray.hpp"

Ray::Ray() : tMax(Infinity), time(0.f), medium(nullptr){};

Ray::Ray(const Vector3f &o, const Vector3f &d, Float tMax, Float time,
         const Medium *medium)
    : o(o.normalized()), d(d.normalized()), tMax(tMax), time(time), medium(medium) {}

Vector3f Ray::operator()(Float t) const { return o + d * t; }