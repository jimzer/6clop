#ifndef NAIVESAMPLERH
#define NAIVESAMPLERH

#include "core/cyclop.hpp"
#include "core/sampler.hpp"

namespace sampler {

class NaiveSampler : public Sampler {
 public:

  NaiveSampler(const int &s);

  Float get1D() const;
  Vector2f get2D() const;
};

}  // namespace sampler

#endif