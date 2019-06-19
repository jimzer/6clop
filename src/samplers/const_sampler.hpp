#ifndef CONSTSAMPLERH
#define CONSTSAMPLERH

#include "core/cyclop.hpp"
#include "core/sampler.hpp"

namespace sampler {

class ConstSampler : public Sampler {
 public:
  const Float cnst;

  ConstSampler(const int &s, const Float &c);

  Float get1D() const;
  Vector2f get2D() const;
};

}  // namespace sampler

#endif