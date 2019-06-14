#include "scene.hpp"

Scene::Scene(const std::vector<std::shared_ptr<hitable::Hitable>> &h)
    : hitables(h){};
