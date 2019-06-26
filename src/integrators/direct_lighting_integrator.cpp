#include "direct_lighting_integrator.hpp"

namespace integrator {

DirectLightingIntegrator::DirectLightingIntegrator(sampler::Sampler *s,
                                                   camera::Camera *c,
                                                   const int &ns)
    : SamplerIntegrator(s, c, ns) {}

}  // namespace integrator