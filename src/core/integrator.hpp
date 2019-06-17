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

  virtual void render(const Scene &scene) = 0;
};

class SamplerIntegrator {
 public:
  sampler::Sampler *sampler;
  camera::Camera *camera;

  SamplerIntegrator(sampler::Sampler *s, camera::Camera *c);
  virtual ~SamplerIntegrator(){};

  void render(const Scene &scene);
  virtual Vector3f li(const Ray &ray, const Scene &scene,
                      const int &depth) const = 0;
};

}  // namespace integrator

#endif