add_executable(
    unit_tests
    core/geometry_test.cpp
    core/ray_test.cpp
    core/transform_test.cpp
    core/filehandle_test.cpp
    cameras/perspective_camera_test.cpp
    )

target_link_libraries(
    unit_tests
    gtest_main
    Eigen3::Eigen
    core
    cameras
    )

add_test(
  NAME
    unit
  COMMAND
    ${CMAKE_BINARY_DIR}/test/unit_tests
  )