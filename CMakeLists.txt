cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(module-example-cpp LANGUAGES CXX)

# include(FindPkgConfig)
# pkg_search_module(MODS libgrpc++-dev)
# find_package(gRPC ${VIAMCPPSDK_GRPC_VERSION_MINIMUM} CONFIG)
# find_package(grpc)

include(FetchContent)

# FetchContent_Declare(
#   viam_rust_utils
#   GIT_REPOSITORY https://github.com/viamrobotics/rust-utils.git
#   GIT_TAG v0.0.27
# )
# FetchContent_MakeAvailable(viam_rust_utils)

# FetchContent_Declare(
#     Corrosion
#     GIT_REPOSITORY https://github.com/corrosion-rs/corrosion.git
#     GIT_TAG v0.4.2
# )
# FetchContent_MakeAvailable(Corrosion)

# FetchContent_GetProperties(viam_rust_utils SOURCE_DIR RUSTUTILS_SOURCEDIR)
# corrosion_import_crate(MANIFEST_PATH "${RUSTUTILS_SOURCEDIR}/Cargo.toml")

# FetchContent_Declare(
#   viam-cpp-sdk
#   # GIT_REPOSITORY https://github.com/viamrobotics/viam-cpp-sdk.git
#   SOURCE_DIR ../../viam-cpp-sdk
#   # SOURCE_SUBDIR src/viam/api
#   # GIT_TAG        816344a7932260307fbcfe0255a0c08afeb448f6
# )

# FetchContent_MakeAvailable(viam-cpp-sdk)
# FetchContent_GetProperties(viam-cpp-sdk SOURCE_DIR VIAM_SOURCEDIR)
# add_library(viam-cpp-sdk INTERFACE)

include(ExternalProject)
ExternalProject_Add(
  viam-cpp-sdk
  GIT_REPOSITORY https://github.com/viamrobotics/viam-cpp-sdk.git
  GIT_TAG        816344a7932260307fbcfe0255a0c08afeb448f6
  CMAKE_ARGS -DVIAMCPPSDK_USE_DYNAMIC_PROTOS=ON
)
# ExternalProject_Get_Property(viam-cpp-sdk INSTALL_RPATH)

# find_package(viam-cpp-sdk-libviamsdk)
# find_package(viam-cpp-sdk-libviamapi)

add_executable(module-example-cpp main.cpp)
# target_include_directories(module-example-cpp PRIVATE "${VIAM_SOURCEDIR}/src")

add_dependencies(module-example-cpp viam-cpp-sdk)
# note: I think this is a bug in how API is exporting its own includes or how protos are generated. shouldn't have to set this
target_include_directories(module-example-cpp PRIVATE "${CMAKE_BINARY_DIR}/viam-cpp-sdk-prefix/src/viam-cpp-sdk-build/install/include/viam/api")
# target_link_libraries(module-example-cpp viam-cpp-sdk::viamapi)
target_link_libraries(module-example-cpp viam-cpp-sdk::viamsdk)
# add_library(viam STATIC viam-cpp-sdk)
# target_include_directories(module-example-cpp PRIVATE viam-cpp-sdk/src)
# target_link_libraries(module-example-cpp PRIVATE viam-cpp-sdk)
