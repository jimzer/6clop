include_directories(${EIGEN3_INCLUDE_DIRS})

add_library(
    core
    core/cyclop.hpp
    core/cyclop.cpp
    core/camera.hpp
    core/hitable.hpp
    core/sampler.hpp
    core/filter.hpp
    core/geometry.hpp
    core/integrator.hpp
    core/integrator.cpp
    core/geometry.cpp
    core/ray.hpp
    core/ray.cpp
    core/transform.hpp
    core/transform.cpp
    core/filehandle.hpp
    core/filehandle.cpp
    core/image_ppm.hpp
    core/image_ppm.cpp
    core/scene.hpp
    core/scene.cpp
    core/film.hpp
    core/film.cpp
)
add_library(
    cameras
    cameras/perspective_camera.hpp
    cameras/perspective_camera.cpp
)

add_library(
    hitables
    hitables/sphere.hpp
    hitables/sphere.cpp
)

add_library(
    integrators
    integrators/hit_integrator.hpp
    integrators/hit_integrator.cpp
)

add_library(
    samplers
    samplers/naive_sampler.hpp
    samplers/naive_sampler.cpp
    samplers/const_sampler.hpp
    samplers/const_sampler.cpp
)

add_library(
    filters
    filters/box_filter.hpp
    filters/box_filter.cpp
)

target_include_directories(core PUBLIC "${CMAKE_CURRENT_SOURCE_DIRECTORY/src}")
target_include_directories(cameras PUBLIC "${CMAKE_CURRENT_SOURCE_DIRECTORY/src}")
target_include_directories(hitables PUBLIC "${CMAKE_CURRENT_SOURCE_DIRECTORY/src}")
target_include_directories(integrators PUBLIC "${CMAKE_CURRENT_SOURCE_DIRECTORY/src}")
target_include_directories(samplers PUBLIC "${CMAKE_CURRENT_SOURCE_DIRECTORY/src}")
target_include_directories(filters PUBLIC "${CMAKE_CURRENT_SOURCE_DIRECTORY/src}")
