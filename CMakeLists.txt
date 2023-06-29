cmake_minimum_required(VERSION 3.5)
project(ground_surface_estimation)

set(DEFAULT_BUILD_TYPE "Release")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-w")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -g -ggdb ${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "-g ${CMAKE_CXX_FLAGS}")

include(cmake/packages.cmake)
include_directories(src)

add_subdirectory(src)
add_subdirectory(test)