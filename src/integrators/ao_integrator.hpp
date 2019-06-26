#ifndef AOINTEGRATORH
#define AOINTEGRATORH

#include "core/cyclop.hpp"
#include "core/integrator.hpp"

namespace integrator {

class AOIntegrator : public SamplerIntegrator {
 public:
  int nSamples;
  AOIntegrator(sampler::Sampler *s, camera::Camera *c, const int &ns, const int &nSamp);

  Vector3f li(const Ray &ray, const Scene &scene, const int &depth) const;
};

}  // namespace integrator

#endif