#ifndef SAMPLERH
#define SAMPLERH

#include "core/cyclop.hpp"

namespace sampler {

class Sampler {
 public:
  int seed;

  Sampler(const int &s) : seed(s){};
  virtual ~Sampler(){};

  virtual Float get1D() const = 0;
  virtual Vector2f get2D() const = 0;
};

}  // namespace sampler

#endif