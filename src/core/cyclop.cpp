#include "cyclop.hpp"

bool solveQuadratic(const double &a, const double &b, const double &c,
                    Float *t0, Float *t1) {
  double discrim = b * b - 4 * a * c;
  if (discrim < 0) {
    return false;
  }
  double rootDiscrim = std::sqrt(discrim);
  double q;
  if (b < 0)
    q = -.5 * (b - rootDiscrim);
  else
    q = -.5 * (b + rootDiscrim);
  *t0 = q / a;
  *t1 = c / q;
  if (*t0 > *t1) std::swap(*t0, *t1);
  return true;
}