#include "ao_integrator.hpp"
#include "core/camera.hpp"
#include "core/hitable.hpp"
#include "core/sampler.hpp"
#include "core/scene.hpp"
#include "core/transform.hpp"

namespace integrator {

AOIntegrator::AOIntegrator(sampler::Sampler *s, camera::Camera *c,
                           const int &ns, const int &nSamp)
    : SamplerIntegrator(s, c, ns), nSamples(nSamp) {}

Vector3f AOIntegrator::li(const Ray &ray, const Scene &scene,
                          const int &depth) const {
  hitable::HitRecord hr;
  Vector3f L;
  if (scene.hit(ray, &hr)) {
    auto worldToShade = transform::coordinateSystem(hr.n);
    auto shadeToWorld = worldToShade.inverse();

    Vector3f wi;
    Float pdf = 1 / (2 * M_PI);
    for (auto i = 0; i < nSamples; i++) {
      Vector2f u = sampler->get2D();
      wi = sampler::uniformSamplerHemisphere(u);
      wi = shadeToWorld(wi, VECTOR);
      Ray shadowRay(hr.p, wi);
      if (!scene.hitCheck(shadowRay)) {
        Float tmp = wi.dot(hr.n) / (pdf * nSamples);
        Vector3f ttmp;
        ttmp.fill(tmp);
        L += ttmp;
      }
    }
  }
  return L;
}

}  // namespace integrator