cmake_minimum_required(VERSION 3.15)

project(what_is_going_on)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")

set(LIB_SRCS
  # src/ILifeGrid.cpp
  src/LifeGrid.cpp
  # src/LifeTemplate.cpp
  # src/Structure.cpp
  src/Vector2.cpp
)
add_library(libraries ${LIB_SRCS})
include_directories(include/)
target_include_directories(libraries
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_subdirectory(external)
add_subdirectory(server)
add_subdirectory(tests)