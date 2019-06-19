#include "hit_integrator.hpp"
#include "core/camera.hpp"
#include "core/hitable.hpp"
#include "core/sampler.hpp"
#include "core/scene.hpp"

namespace integrator {

HitIntegrator::HitIntegrator(sampler::Sampler *s, camera::Camera *c,
                             const int &ns)
    : SamplerIntegrator(s, c, ns){};

Vector3f HitIntegrator::li(const Ray &ray, const Scene &scene,
                           const int &depth) const {
  hitable::HitRecord hr;
  if (scene.hit(ray, &hr)) {
    Float c = hr.n.dot(-ray.d);
    return Vector3f(1, 1, 1) * c;
  } else {
    return Vector3f(1, 0, 0);
  }
}

}  // namespace integrator