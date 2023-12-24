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

set(external_include_dirs
  ${external_include_dirs}
  ${zlib_content_SOURCE_DIR} # some weird renaming business happens here with zconf.h -> zconf.h.included
  ${zlib_content_BINARY_DIR} # zconf.h is untouched here though
)
include_directories(${external_include_dirs})
set(external_include_dirs ${external_include_dirs} PARENT_SCOPE)