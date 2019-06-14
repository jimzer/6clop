#include "naive_sampler.hpp"

namespace sampler {

NaiveSampler::NaiveSampler(const int &s) : Sampler(s){};

Float NaiveSampler::get1D() const { return drand48(); };

Vector2f NaiveSampler::get2D() const { return Vector2f(drand48(), drand48()); }
}  // namespace sampler