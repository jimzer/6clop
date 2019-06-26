#ifndef DIRECTLIGHTINGINTEGRATORH
#define DIRECTLIGHTINGINTEGRATORH

#include "core/cyclop.hpp"
#include "core/integrator.hpp"

namespace integrator {

class DirectLightingIntegrator : public SamplerIntegrator {
 public:
  DirectLightingIntegrator(sampler::Sampler *s, camera::Camera *c, const int &ns);

  Vector3f li(const Ray &ray, const Scene &scene, const int &depth) const;
};

}  // namespace integrator

#endif