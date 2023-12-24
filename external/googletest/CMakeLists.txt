cmake_minimum_required(VERSION 3.24)

set(CMAKE_C_STANDARD 11)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.13.x
  GIT_SHALLOW ON
  GIT_SUBMODULES ""
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(external_include_dirs
  ${external_include_dirs}
  ${googletest_SOURCE_DIR}
  ${googletest_BINARY_DIR}
)
include_directories(${external_include_dirs})
set(external_include_dirs ${external_include_dirs} PARENT_SCOPE)