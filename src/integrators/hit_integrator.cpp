#include "hit_integrator.hpp"
#include "core/camera.hpp"
#include "core/sampler.hpp"

namespace integrator {

HitIntegrator::HitIntegrator(sampler::Sampler *s, camera::Camera *c)
    :SamplerIntegrator(s, c){};

Vector3f HitIntegrator::li(const Ray &ray, const Scene &scene,
                           const int &depth) const {
  return Vector3f(100, 0, 0);
}

}  // namespace integrator