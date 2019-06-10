cmake_minimum_required(VERSION 3.14)

project(
    Cyclop
    VERSION 1.0
    DESCRIPTION "A Ray Tracer Experiment"
    LANGUAGES CXX
)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")

set(TBB /usr/include/tbb)

find_package(Eigen3 3.3.7 REQUIRED NO_MODULE)

add_definitions(-DEIGEN_INITIALIZE_MATRICES_BY_ZERO=1)

add_executable(main main.cpp)
add_subdirectory(src)

target_compile_features(main PRIVATE cxx_std_17)


target_link_libraries (main PUBLIC Eigen3::Eigen)
target_link_libraries(main PRIVATE core)
target_link_libraries(main PRIVATE cameras)


include(cmake/googletest.cmake)
fetch_googletest(
   ${PROJECT_SOURCE_DIR}/cmake
   ${PROJECT_BINARY_DIR}/googletest
   )

enable_testing()
add_subdirectory(test)