#ifndef HITINTEGRATORH
#define HITINTEGRATORH

#include "core/cyclop.hpp"
#include "core/integrator.hpp"

namespace integrator {

class HitIntegrator : public SamplerIntegrator {
 public:
  HitIntegrator(sampler::Sampler *s, camera::Camera *c);

  Vector3f li(const Ray &ray, const Scene &scene, const int &depth) const;
};

}  // namespace integrator

#endif