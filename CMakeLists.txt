cmake_minimum_required(VERSION 3.10)
project(HashTableExperiment)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Release mode is crucial for benchmarking (O3 optimization)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(experiment ${SOURCES})
target_include_directories(experiment PRIVATE src)
