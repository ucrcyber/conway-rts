cmake_minimum_required(VERSION 3.24)
set(CMAKE_C_STANDARD 11)
include(FetchContent)
FetchContent_Declare(
  libuv_content
  GIT_REPOSITORY https://github.com/libuv/libuv
  GIT_TAG v1.x
  GIT_SHALLOW ON
  GIT_SUBMODULES ""
)
FetchContent_MakeAvailable(libuv_content)
target_link_libraries(uv uv_a)