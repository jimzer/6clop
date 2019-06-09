add_executable(
    unit_tests
    geometry_test.cpp
    ray_test.cpp
    transform_test.cpp
    filehandle_test.cpp
    )

target_link_libraries(
    unit_tests
    gtest_main
    Eigen3::Eigen
    core
    )

add_test(
  NAME
    unit
  COMMAND
    ${CMAKE_BINARY_DIR}/test/unit_tests
  )