#include "film.hpp"

namespace film {

Film::Film(const std::string &n, const Vector2i &res, filter::Filter *f)
    : name(n),
      resolution(res),
      filter(f),
      pixels(std::vector<Pixel>(res.x() * res.y())),
      im(ImagePPM(n, res.x(), res.y())){};

Pixel *Film::getPixel(const Vector2i &pixelPos) {
  int pixelIdx = pixelPos.y() * resolution.x() + pixelPos.x();
  Pixel *p = &pixels[pixelIdx];
  return p;
}

void Film::addSample(const Vector2f &pFilm, Vector3f radiance,
                     const Float &sampleWeight) {
  Vector2i minPixel, maxPixel;
  getContribPixels(pFilm, &minPixel, &maxPixel);
  for (auto x = minPixel.x(); x <= maxPixel.x(); x++) {
    for (auto y = minPixel.y(); y <= maxPixel.y(); y++) {
      Vector2i pos(x, y);
      ASSERT(x >= 0 && x < resolution.x(),
             "Out of bounds for x discrete pixel position");
      ASSERT(y >= 0 && y < resolution.y(),
             "Out of bounds for y discrete pixel position");
      Vector2f relativeSamplePos(x + 0.5 - pFilm.x(), y + 0.5 - pFilm.y());
      Float filterWeight = filter->eval(relativeSamplePos);
      Pixel *pixel = getPixel(pos);
      pixel->contribSum += radiance * sampleWeight * filterWeight;
      pixel->filterWeightSum += filterWeight;
    }
  }
}

void Film::writeImage() {
  int total = resolution.x() * resolution.y();
  std::vector<RGB> rgbs(total);

  for (auto i = 0; i < total; i++) {
    Pixel pixel = pixels[i];
    Vector3f radiance = pixel.contribSum / pixel.filterWeightSum;
    // Reinhard tone mapping
    radiance = radiance.array() / (radiance + Vector3f(1, 1, 1)).array();
    // Gamma correction
    radiance = radiance.array().sqrt();
    RGB rgb = {radiance.x(), radiance.y(), radiance.z()};
    rgbs[i] = rgb;
  }

  im.writeRGBs(rgbs);
}

void Film::getContribPixels(const Vector2f &pFilm, Vector2i *minPixel,
                            Vector2i *maxPixel) const {
  Float radius = filter->radius;
  int minX = std::ceil(pFilm.x() - 0.5 - radius);
  int maxX = std::floor(pFilm.x() - 0.5 + radius);
  int minY = std::ceil(pFilm.y() - 0.5 - radius);
  int maxY = std::floor(pFilm.y() - 0.5 + radius);

  minX = std::max(0, minX);
  minY = std::max(0, minY);
  maxX = std::min(maxX, resolution.x() - 1);
  maxY = std::min(maxY, resolution.y() - 1);

  *minPixel = Vector2i(minX, minY);
  *maxPixel = Vector2i(maxX, maxY);
}

geometry::Bound2i Film::getPixelsBound() const {
  return geometry::Bound2i(Vector2i(), resolution - Vector2i(1, 1));
}

}  // namespace film