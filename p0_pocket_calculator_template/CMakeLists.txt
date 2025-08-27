cmake_minimum_required(VERSION 3.11 FATAL_ERROR)
project(pocket_calculator)

set(CMAKE_BUILD_TYPE RelWithDebInfo)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

find_package(GTest REQUIRED)

# Hello world executable.
add_executable(hello_world src/1_hello_world.cpp)

# Go blue executable.
add_executable(go_blue src/2_go_blue.cpp)

# Fight song executable.
add_executable(fight_song src/3_fight_song.cpp)

# Eliza executable.
add_executable(eliza src/4_eliza.cpp)

# Calculator operation executable.
add_executable(calc_op src/5_calc_op.cpp)

# Pocket calculaotr executable.
add_executable(pocket_calculator src/6_pocket_calc.cpp
  src/common/utils.cpp
)
target_include_directories(pocket_calculator PRIVATE
  include
)

# TESTS
enable_testing()

# Public test cases.
add_executable(test_public test/test_public.cpp
  src/common/utils.cpp
)
target_link_libraries(test_public GTest::gtest_main)
target_include_directories(test_public PRIVATE
  include
  test
)
gtest_discover_tests(test_public)
