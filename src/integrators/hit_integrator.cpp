#include "hit_integrator.hpp"
#include "core/camera.hpp"
#include "core/hitable.hpp"
#include "core/sampler.hpp"
#include "core/scene.hpp"

namespace integrator {

HitIntegrator::HitIntegrator(sampler::Sampler *s, camera::Camera *c,
                             const int &ns, const Vector3f &bc, const Vector3f &hc)
    : SamplerIntegrator(s, c, ns), backgroudColor(bc), hitColor(hc) {};

Vector3f HitIntegrator::li(const Ray &ray, const Scene &scene,
                           const int &depth) const {
  hitable::HitRecord hr;
  if (scene.hit(ray, &hr)) {
    Float c = hr.n.dot(-ray.d);
    return hitColor * c;
  } else {
    return backgroudColor;
  }
}

}  // namespace integrator