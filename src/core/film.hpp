#ifndef FILMH
#define FILMH

#include "core/cyclop.hpp"
#include "core/filter.hpp"
#include "core/image_ppm.hpp"

namespace film {

struct Pixel {
  Vector3f contribSum = Vector3f();
  Float filterWeightSum = 0.f;
};

struct RGB {
  Float R;
  Float G;
  Float B;
};

class Film {
 public:
  std::string name;
  Vector2i resolution;
  filter::Filter *filter;
  std::vector<Pixel> pixels;
  ImagePPM im;

  Film(const std::string &n, const Vector2i &res, filter::Filter *f);

  Pixel *getPixel(const Vector2i &pixelPos);

  void addSample(const Vector2f &pFilm, Vector3f radiance,
                 const Float &sampleWeight = 1.0);
  void writeImage();

  void getContribPixels(const Vector2f &pFilm, Vector2i *minPixel,
                        Vector2i *maxPixel) const;
};

}  // namespace film

#endif