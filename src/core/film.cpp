#include "film.hpp"

namespace film {

Film::Film(const Vector2i &res, filter::Filter *f)
    : resolution(res),
      filter(f),
      pixels(std::vector<Pixel>(res.x() * res.y())){};

Pixel *Film::getPixel(const Vector2i &pixelPos) {
  int pixelIdx = pixelPos.x() * resolution.x() + pixelPos.y();
  Pixel* p = &pixels[pixelIdx];
  return p;
}

void Film::addSample(const Vector2f &pFilm, Vector3f radiance,
                     const Float &sampleWeight) {
  Vector2i minPixel, maxPixel;
  getContribPixels(pFilm, filter->radius, &minPixel, &maxPixel);
  for (auto x = minPixel.x(); x <= maxPixel.x(); x++) {
    for (auto y = minPixel.y(); y <= maxPixel.y(); y++) {
      Vector2i pos(x, y);
      Pixel *pixel = getPixel(pos);
      pixel->contribSum += radiance;
      pixel->filterWeightSum += sampleWeight;
    }
  }
}

void getContribPixels(const Vector2f &pFilm, const Float &radius,
                      Vector2i *minPixel, Vector2i *maxPixel) {
  int minX = std::ceil(pFilm.x() - 0.5 - radius);
  int maxX = std::floor(pFilm.x() - 0.5 + radius);
  int minY = std::ceil(pFilm.y() - 0.5 - radius);
  int maxY = std::floor(pFilm.y() - 0.5 + radius);

  *minPixel = Vector2i(minX, minY);
  *maxPixel = Vector2i(maxX, maxY);
}

}  // namespace film