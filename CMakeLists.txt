# this cmake modified from lab-04 and lab-06

cmake_minimum_required(VERSION 3.15)

set(CMAKE_TOOLCHAIN_FILE ${PROJECT_BINARY_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "Vcpkg toolchain file")
include(./vcpkg/scripts/buildsystems/vcpkg.cmake)

project(what_is_going_on)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")

configure_file(CMakeLists.txt.in ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/CMakeLists.txt)
execute_process (
  COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
)
if (result)
  message(FATAL_ERROR "Cmake step failed: ${result}")
endif()

execute_process (
  COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
)
if (result)
  message(FATAL_ERROR "Build step failed: ${result}")
endif()

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory (
  ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/googletest-src
  ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/googletest-build
  EXCLUDE_FROM_ALL
)

set(LIB_SRCS
  src/dummy.cpp
)
add_library(libraries ${LIB_SRCS})
target_include_directories(libraries
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

find_library(USOCKETS_LIB_DEBUG usocketsd)
find_library(USOCKETS_LIB_RELEASE usockets)
find_path(USOCKETS_INCLUDE_DIR include/libusockets.h)

target_include_directories(libraries PRIVATE ${USOCKETS_INCLUDE_DIR})
target_link_libraries(libraries PRIVATE $<$<CONFIG:Debug>:${USOCKETS_LIB_DEBUG}> $<$<CONFIG:Release>:${USOCKETS_LIB_RELEASE}>)

add_subdirectory(external)

include_directories(./vcpkg/installed/x64-linux/include) # this makes include happy but some vcpkg things arent there??

target_link_libraries(libraries PRIVATE z uWebSockets)

add_subdirectory(server)
