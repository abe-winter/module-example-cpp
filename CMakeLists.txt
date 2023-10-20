cmake_minimum_required(VERSION 3.7 FATAL_ERROR)

project(module-example-cpp LANGUAGES CXX)

option(FETCH_GIT "fetch from git instead of using debian package")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

FILE(GLOB sources src/*.cpp)
add_executable(module-example-cpp ${sources})

if (FETCH_GIT)
    include(FetchContent)
    FetchContent_Declare(
        viam-cpp-sdk
        GIT_REPOSITORY https://github.com/viamrobotics/viam-cpp-sdk.git
        GIT_TAG main
        # SOURCE_DIR ${CMAKE_SOURCE_DIR}/../viam-cpp-sdk
        CMAKE_ARGS -DVIAMCPPSDK_USE_DYNAMIC_PROTOS=ON
        FIND_PACKAGE_ARGS
    )
    FetchContent_MakeAvailable(viam-cpp-sdk)

    target_include_directories(module-example-cpp PRIVATE PkgConfig::VIAMSDK PkgConfig::VIAMAPI)
    target_link_libraries(module-example-cpp PRIVATE PkgConfig::VIAMSDK PkgConfig::VIAMAPI)
else()
    find_package(PkgConfig REQUIRED)
    pkg_search_module(VIAMSDK REQUIRED IMPORTED_TARGET viam-cpp-sdk-libviamsdk)
    pkg_search_module(VIAMAPI REQUIRED IMPORTED_TARGET viam-cpp-sdk-libviamapi)

    target_link_libraries(module-example-cpp PRIVATE viam-cpp-sdk::viamsdk)
endif()
