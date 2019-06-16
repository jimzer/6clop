#include "core/image_ppm.hpp"
#include "core/cyclop.hpp"
#include "core/filehandle.hpp"
#include "core/film.hpp"
#include "gtest/gtest.h"

using namespace film;

TEST(imagePPM, constructor) {
  std::string name = "test-ppm.ppm";
  ImagePPM im(name, 10, 10);
  ASSERT_NO_THROW();
}

TEST(imagePPM, writeRGBs) {
  std::string name = "test-ppm.ppm";
  ImagePPM im(name, 100, 100);

  std::vector<RGB> rgbs;

  int total = im.nx * im.ny;

  for (Float i = 0; i < total; i++) {
    Float val = i / total;
    RGB rgb = {val, val, val};
    rgbs.push_back(rgb);
  }
  im.writeRGBs(rgbs);

  ASSERT_NO_THROW();

  FileHandle fh2("test-ppm.ppm", READ);
  std::string str;
  str = fh2.readLine();
  ASSERT_EQ(str, "P3");
  str = fh2.readLine();
  ASSERT_EQ(str, "100 100");
  str = fh2.readLine();
  ASSERT_EQ(str, "255");
  for (Float i = 0; i < total; i++) {
    Float val = i / total;
    int rgbVal = (int)(val * 255.99);
    std::stringstream ss;
    ss << rgbVal << " " << rgbVal << " " << rgbVal;
    str = fh2.readLine();
    ASSERT_EQ(str, ss.str());
  }
}
