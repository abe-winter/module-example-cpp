cmake_minimum_required(VERSION 3.7 FATAL_ERROR)

project(module-example-cpp LANGUAGES CXX)

set(BUILD_SHARED_LIBS OFF)

include(FetchContent)
FetchContent_Declare(
  viam-cpp-sdk
  GIT_REPOSITORY https://github.com/viamrobotics/viam-cpp-sdk.git
  GIT_TAG        816344a7932260307fbcfe0255a0c08afeb448f6
  CMAKE_ARGS -DVIAMCPPSDK_USE_DYNAMIC_PROTOS=ON -DCMAKE_INSTALL_PREFIX=/usr/local -DBUILD_SHARED_LIBS=OFF
  FIND_PACKAGE_ARGS
)
FetchContent_MakeAvailable(viam-cpp-sdk)

add_executable(module-example-cpp main.cpp)

add_dependencies(module-example-cpp viam-cpp-sdk::viamsdk viam-cpp-sdk::viamapi)

target_link_libraries(module-example-cpp PRIVATE viam-cpp-sdk::viamsdk viam-cpp-sdk::viamapi)
