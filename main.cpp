#include <iostream>

#include <tbb/task_group.h>
#include <Eigen/Core>

#include <math.h>
#include <type_traits>

#include "core/cyclop.hpp"
#include "core/film.hpp"
#include "core/ray.hpp"
#include "core/transform.hpp"
#include "filters/box_filter.hpp"
#include "integrators/hit_integrator.hpp"
#include "samplers/naive_sampler.hpp"
#include "cameras/perspective_camera.hpp"

using namespace camera;
using namespace film;
using namespace filter;
using namespace integrator;
using namespace sampler;

int main() {
  Eigen::Matrix<float, 3, 3> m;
  std::cout << m << std::endl;

}