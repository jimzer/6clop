#include "image_ppm.hpp"
#include "core/film.hpp"

ImagePPM::ImagePPM(const std::string &n, const int &x, const int &y)
    : name(n), nx(x), ny(y), fh(FileHandle(n, WRITE)) {
  std::stringstream ss;
  ss << "P3\n" << nx << " " << ny << "\n255\n";
  fh.writeLine(ss);
  ss.clear();
}

void ImagePPM::writeRGBs(std::vector<film::RGB> &rgbs) {
  std::stringstream ss;
  for (auto &&rgb : rgbs) {
    ss << (int)(rgb.R * 255.99) << " " << (int)(rgb.G * 255.99) << " "
       << (int)(rgb.B * 255.99) << "\n";
    fh.writeLine(ss);
    ss.clear();
  }
}