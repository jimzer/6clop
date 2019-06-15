#include "core/image_ppm.hpp"
#include "core/cyclop.hpp"
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
}