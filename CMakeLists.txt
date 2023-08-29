cmake_minimum_required(VERSION 3.7 FATAL_ERROR)

project(module-example-cpp LANGUAGES CXX)

include(ExternalProject)
ExternalProject_Add(
  viam-cpp-sdk
  GIT_REPOSITORY https://github.com/viamrobotics/viam-cpp-sdk.git
  GIT_TAG        816344a7932260307fbcfe0255a0c08afeb448f6
  CMAKE_ARGS -DVIAMCPPSDK_USE_DYNAMIC_PROTOS=ON
)

add_executable(module-example-cpp main.cpp)

add_dependencies(module-example-cpp viam-cpp-sdk)
# todo: is there a way to inherit the include dir from the dependency?
target_include_directories(module-example-cpp PRIVATE "${CMAKE_BINARY_DIR}/viam-cpp-sdk-prefix/src/viam-cpp-sdk-build/install/include/viam/api")

find_package(viam-cpp-sdk CONFIG REQUIRED viamsdk)
target_link_libraries(module-example-cpp PRIVATE viam-cpp-sdk::viamsdk)
