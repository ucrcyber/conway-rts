cmake_minimum_required(VERSION 3.24)
include(FetchContent)
FetchContent_Declare(
  uWebSockets_content
  GIT_REPOSITORY https://github.com/uNetworking/uWebSockets
  GIT_TAG v20.37.0
  GIT_SHALLOW ON
  GIT_SUBMODULES ""
)
FetchContent_MakeAvailable(uWebSockets_content)
add_library(uWebSockets INTERFACE)
target_include_directories(uWebSockets INTERFACE ${uwebsockets_content_SOURCE_DIR}/src/ ${CMAKE_CURRENT_BINARY_DIR}/${ZLIB_LIBRARY})
target_link_libraries(uWebSockets INTERFACE uSockets uv zlibstatic)
