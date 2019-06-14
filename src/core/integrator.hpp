#ifndef INTEGRATORH
#define INTEGRATORH

#include "core/cyclop.hpp"

class Ray;
class Scene;
namespace sampler {
class Sampler;
}
namespace camera {
class Camera;
}

namespace integrator {

class Integrator {
 public:
  Integrator(){};
  virtual ~Integrator(){};

  virtual void render(const Scene &scene) const = 0;
};

class SamplerIntegrator : public Integrator {
 public:
  SamplerIntegrator(const sampler::Sampler &sampler, const camera::Camera &camera);

  virtual void render(const Scene &scene) const = 0;
  virtual Vector3f li(const Ray &ray, const Scene &scene,
                      const sampler::Sampler &sampler, const int &depth) const = 0;
};

}  // namespace integrator

#endif