# Example CMakeLists.txt of super-project which contains gflags source tree:
cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)

project(Foo)

add_subdirectory(gflags)

add_executable(foo foo.cc)
target_link_libraries(foo gflags)
