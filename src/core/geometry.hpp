#ifndef GEOMTRYH
#define GEOMTRYH

#include "core/cyclop.hpp"

namespace geometry {
Vector4f toHomog(const Vector3f &v, Geomtype g);
Vector3f toRegular(const Vector4f &v);
Float toRadians(Float &d);
Float toDegrees(Float &r);

template <typename T>
class Bound2 {
 private:
  typedef Eigen::Matrix<T, 2, 1> Vector2;

 public:
  Vector2 pMin;
  Vector2 pMax;

  Bound2(const Vector2 &pmin, const Vector2 &pmax) : pMin(pmin), pMax(pmax){};
  bool operator==(const Bound2<T> &b) const {
    return b.pMin == pMin && b.pMax == pMax;
  }
  bool operator!=(const Bound2<T> &b) const {
    return b.pMin != pMin || b.pMax != pMax;
  }
};

typedef Bound2<int> Bound2i;
typedef Bound2<Float> Bound2f;

class Bound2iIterator {
 private:
  void advance() {
    point.x() += 1;
    if (point.x() > bound->pMax.x()) {
      point.x() = bound->pMin.x();
      point.y() += 1;
    }
  }

 public:
  Vector2i point;
  const Bound2i *bound;
  Bound2iIterator(const Bound2i *b, const Vector2i &p) : bound(b), point(p) {}
  bool operator!=(const Bound2iIterator &bi) {
    return (bi.point != point) || (*bound != *bi.bound);
  }
  bool operator==(const Bound2iIterator &bi) {
    return (bi.point == point) && (*bound == *bi.bound);
  }
  Vector2i &operator*() { return point; }
  Bound2iIterator operator++() {
    advance();
    return *this;
  }
  Bound2iIterator operator++(int) {
    Bound2iIterator old = *this;
    advance();
    return old;
  }
};

inline Bound2iIterator begin(const Bound2i &b) {
  return Bound2iIterator(&b, b.pMin);
}

inline Bound2iIterator end(const Bound2i &b) {
  Vector2i end(b.pMin.x(), b.pMax.y() + 1);
  return Bound2iIterator(&b, end);
}

}  // namespace geometry

#endif