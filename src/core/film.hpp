#ifndef FILMH
#define FILMH

#include "core/cyclop.hpp"
#include "core/filter.hpp"

namespace film {

struct Pixel {
  Vector3f contribSum = Vector3f();
  Float filterWeightSum = 0.f;
};

class Film {
 public:
  Vector2i resolution;
  filter::Filter *filter;
  std::vector<Pixel> pixels;

  Film(const Vector2i &res, filter::Filter *f);

  Pixel *getPixel(const Vector2i &pixelPos);

  void addSample(const Vector2f &pFilm, Vector3f radiance,
                 const Float &sampleWeight);
};

void getContribPixels(const Vector2f &pFilm, const Float &radius,
                      Vector2i *minPixel, Vector2i *maxPixel);

}  // namespace film

#endif