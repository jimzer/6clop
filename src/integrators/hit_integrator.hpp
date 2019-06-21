#ifndef HITINTEGRATORH
#define HITINTEGRATORH

#include "core/cyclop.hpp"
#include "core/integrator.hpp"

namespace integrator {

class HitIntegrator : public SamplerIntegrator {
 public:
  Vector3f backgroudColor;
  Vector3f hitColor;
  HitIntegrator(sampler::Sampler *s, camera::Camera *c, const int &ns,
                const Vector3f &bc, const Vector3f &hc);

  Vector3f li(const Ray &ray, const Scene &scene, const int &depth) const;
};

}  // namespace integrator

#endif