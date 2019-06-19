#include "const_sampler.hpp"

namespace sampler {

ConstSampler::ConstSampler(const int &s, const Float &c)
    : Sampler(s), cnst(c){};

Float ConstSampler::get1D() const { return cnst; };

Vector2f ConstSampler::get2D() const { return Vector2f(cnst, cnst); }
}  // namespace sampler