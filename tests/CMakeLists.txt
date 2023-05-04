cmake_minimum_required(VERSION 3.15)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")

add_executable(runAllTests
  sampleTest.cpp
  Vector2.cpp
  LifeTemplate.cpp
  LifeGrid.cpp
)

target_link_libraries(runAllTests gmock gtest gtest_main libraries)
