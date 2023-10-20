cmake_minimum_required(VERSION 3.7 FATAL_ERROR)

project(module-example-cpp LANGUAGES CXX)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

find_package(PkgConfig REQUIRED)
pkg_search_module(VIAMSDK REQUIRED IMPORTED_TARGET viam-cpp-sdk-libviamsdk)
pkg_search_module(VIAMAPI REQUIRED IMPORTED_TARGET viam-cpp-sdk-libviamapi)

FILE(GLOB sources src/*.cpp)
add_executable(module-example-cpp ${sources})
target_include_directories(module-example-cpp PRIVATE PkgConfig::VIAMSDK PkgConfig::VIAMAPI)
target_link_libraries(module-example-cpp PRIVATE PkgConfig::VIAMSDK PkgConfig::VIAMAPI)
