cmake_minimum_required(VERSION 3.7 FATAL_ERROR)

project(module-example-cpp LANGUAGES CXX)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include(FetchContent)
FetchContent_Declare(
  viam-cpp-sdk
  GIT_REPOSITORY https://github.com/viamrobotics/viam-cpp-sdk.git
  GIT_TAG 2e5fd316ce43410fb59778220fb53128d613892a
  # SOURCE_DIR ${CMAKE_SOURCE_DIR}/../viam-cpp-sdk
  CMAKE_ARGS -DVIAMCPPSDK_USE_DYNAMIC_PROTOS=ON
  EXCLUDE_FROM_ALL
  FIND_PACKAGE_ARGS
)
FetchContent_MakeAvailable(viam-cpp-sdk)

FILE(GLOB sources src/*.cpp)
add_executable(module-example-cpp ${sources})
target_link_libraries(module-example-cpp PRIVATE viam-cpp-sdk::viamsdk)
