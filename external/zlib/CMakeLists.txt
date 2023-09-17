cmake_minimum_required(VERSION 3.24)
set(CMAKE_C_STANDARD 11)
include(FetchContent)
FetchContent_Declare(
  zlib_content
  GIT_REPOSITORY https://github.com/madler/zlib
  GIT_TAG v1.3
  GIT_SHALLOW ON
  GIT_SUBMODULES ""
)
FetchContent_MakeAvailable(zlib_content)