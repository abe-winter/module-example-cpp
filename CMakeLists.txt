cmake_minimum_required(VERSION 3.7 FATAL_ERROR)

project(module-example-cpp LANGUAGES CXX)

set(BUILD_SHARED_LIBS OFF)
# CMP0077 passes down options
# set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
set(VIAMCPPSDK_STATIC_RUST ON)
# set(BUILD_SHARED_LIBS OFF)
# set(VIAMCPPSDK_USE_DYNAMIC_PROTOS ON)
# -DCMAKE_LINK_SEARCH_START_STATIC=ON

include(FetchContent)
FetchContent_Declare(
  viam-cpp-sdk
  GIT_REPOSITORY https://github.com/viamrobotics/viam-cpp-sdk.git
  GIT_TAG corrosion
  # SOURCE_DIR ${CMAKE_SOURCE_DIR}/../viam-cpp-sdk
  CMAKE_ARGS -DVIAMCPPSDK_USE_DYNAMIC_PROTOS=ON -DBUILD_SHARED_LIBS=OFF -DCMAKE_LINK_SEARCH_START_STATIC=ON -DVIAMCPPSDK_STATIC_RUST=ON
  FIND_PACKAGE_ARGS
)
FetchContent_MakeAvailable(viam-cpp-sdk)

add_executable(module-example-cpp main.cpp)

add_dependencies(module-example-cpp viam-cpp-sdk::viamsdk viam-cpp-sdk::viamapi)

# todo: get this from RUST_OUTPUT from viam-cpp-sdk or export the library
target_link_directories(module-example-cpp PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/_deps/viam-cpp-sdk-build/)
target_link_libraries(module-example-cpp PRIVATE viam-cpp-sdk::viamsdk viam-cpp-sdk::viamapi)
