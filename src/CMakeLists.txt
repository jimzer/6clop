include_directories(${EIGEN3_INCLUDE_DIRS})

add_library(
    core
    core/cyclop.hpp
    core/cyclop.cpp
    core/camera.hpp
    core/hitable.hpp
    core/filter.hpp
    core/geometry.hpp
    core/light.hpp
    core/material.hpp
    core/integrator.hpp
    core/integrator.cpp
    core/sampler.hpp
    core/sampler.cpp
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
    hitables/brute_aggregate.hpp
    hitables/brute_aggregate.cpp
)

add_library(
    integrators
    integrators/hit_integrator.hpp
    integrators/hit_integrator.cpp
    integrators/ao_integrator.hpp
    integrators/ao_integrator.cpp
    integrators/direct_lighting_integrator.hpp
    integrators/direct_lighting_integrator.cpp
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

add_library(
    lights
    lights/point_light.hpp
    lights/point_light.cpp
)

add_library(
    materials
    materials/matte_material.hpp
    materials/matte_material.cpp
    materials/dielectric_material.hpp
    materials/dielectric_material.cpp
)


target_include_directories(core PUBLIC "${CMAKE_CURRENT_SOURCE_DIRECTORY/src}")
target_include_directories(cameras PUBLIC "${CMAKE_CURRENT_SOURCE_DIRECTORY/src}")
target_include_directories(hitables PUBLIC "${CMAKE_CURRENT_SOURCE_DIRECTORY/src}")
target_include_directories(integrators PUBLIC "${CMAKE_CURRENT_SOURCE_DIRECTORY/src}")
target_include_directories(samplers PUBLIC "${CMAKE_CURRENT_SOURCE_DIRECTORY/src}")
target_include_directories(filters PUBLIC "${CMAKE_CURRENT_SOURCE_DIRECTORY/src}")
target_include_directories(lights PUBLIC "${CMAKE_CURRENT_SOURCE_DIRECTORY/src}")
target_include_directories(materials PUBLIC "${CMAKE_CURRENT_SOURCE_DIRECTORY/src}")
