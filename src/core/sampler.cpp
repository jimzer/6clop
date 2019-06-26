#include "sampler.hpp"

namespace sampler {

Vector3f uniformSamplerHemisphere(const Vector2f &u) {
  float z = u.x();
  float r = std::sqrt(std::max(0., 1. - z * z));
  float phi = 2 * M_PI * u.y();
  return Vector3f(r * std::cos(phi), r * std::sin(phi), z);
}

}  // namespace sampler
