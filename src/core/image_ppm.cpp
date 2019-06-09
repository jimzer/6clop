#include "image_ppm.hpp"

ImagePPM::ImagePPM(const std::string &n, const int &x, const int &y)
    : name(n), nx(x), ny(y), fh(FileHandle(name, WRITE)) {
  fh.writeLine("PPM");
  std::stringstream dim;
  dim << nx << " " << ny << std::endl;
  fh.writeLine(dim);
}