#include <iostream>

#include <tbb/task_group.h>
#include <Eigen/Core>

#include <math.h>
#include <type_traits>


int main() {
  Eigen::Matrix<float, 3, 3> m;
  std::cout << m << std::endl;

}