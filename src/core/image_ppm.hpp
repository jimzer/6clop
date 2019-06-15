#ifndef IMAGEPPMH
#define IMAGEPPMH

#include <array>
#include "core/cyclop.hpp"
#include "core/filehandle.hpp"

namespace film {
  struct RGB;
}

class ImagePPM {
 private:
  FileHandle fh;

 public:
  int nx;
  int ny;
  std::string name;

  ImagePPM(const std::string &n, const int &x, const int &y);

  void writeRGBs(std::vector<film::RGB> &rgbs);


};

#endif