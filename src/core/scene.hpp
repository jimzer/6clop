#ifndef SCENEH
#define SCENEH

#include <memory>
#include "core/cyclop.hpp"
#include "core/hitable.hpp"

class Scene {
 public:
  std::vector<std::shared_ptr<hitable::Hitable>> hitables;

  Scene(const std::vector<std::shared_ptr<hitable::Hitable>> &h);
};

#endif