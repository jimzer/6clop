#include "integrator.hpp"
#include "camera.hpp"
#include "film.hpp"
#include "geometry.hpp"
#include "ray.hpp"
#include "sampler.hpp"
#include "scene.hpp"

namespace integrator {
SamplerIntegrator::SamplerIntegrator(sampler::Sampler *s, camera::Camera *c,
                                     const int &ns)
    : sampler(s), camera(c), samplesPerPixel(ns){};

void SamplerIntegrator::render(const Scene &scene) {
  geometry::Bound2i b = camera->film->getPixelsBound();

  for (const Vector2i pixelPos : b) {
    for (int i = 0; i < samplesPerPixel; i++) {
      Vector2f shift = sampler->get2D();
      Vector2f filmPos(pixelPos.x() + shift.x(), pixelPos.y() + shift.y());
      camera::CameraSample cs;
      cs.filmSample = filmPos;
      cs.lensSample = sampler->get2D();

      Ray ray = camera->generateRay(cs);
      Vector3f radiance = li(ray, scene, 10);
      camera->film->addSample(filmPos, radiance, 1.0);
    }
  }
  camera->film->writeImage();
}
}  // namespace integrator