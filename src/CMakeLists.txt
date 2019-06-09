include_directories(${EIGEN3_INCLUDE_DIRS})

add_library(
    core
    core/cyclop.hpp
    core/cyclop.cpp
    core/geometry.hpp
    core/geometry.cpp
    core/ray.hpp
    core/ray.cpp
    core/transform.hpp
    core/transform.cpp
    core/camera.hpp
    core/camera.cpp
)

target_include_directories(core PUBLIC "${CMAKE_CURRENT_SOURCE_DIRECTORY/src}")