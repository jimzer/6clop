add_executable(
    unit_tests
    core/cyclop_test.cpp
    core/geometry_test.cpp
    core/ray_test.cpp
    core/transform_test.cpp
    core/filehandle_test.cpp
    core/film_test.cpp
    core/image_ppm_test.cpp
    core/scene_test.cpp
    cameras/perspective_camera_test.cpp
    hitables/sphere_test.cpp
    hitables/brute_aggregate_test.cpp
    integrators/hit_integrator_test.cpp
    integrators/ao_integrator_test.cpp
    samplers/naive_sampler_test.cpp
    filters/box_filter_test.cpp
    )

target_link_libraries(unit_tests gtest_main)
target_link_libraries(unit_tests Eigen3::Eigen)
target_link_libraries(unit_tests core)
target_link_libraries(unit_tests cameras core)
target_link_libraries(unit_tests hitables core)
target_link_libraries(unit_tests samplers core)
target_link_libraries(unit_tests filters core)
target_link_libraries(unit_tests integrators core)
target_link_libraries(unit_tests lights core)
target_link_libraries(unit_tests materials core)

add_test(
  NAME
    unit
  COMMAND
    ${CMAKE_BINARY_DIR}/test/unit_tests
  )