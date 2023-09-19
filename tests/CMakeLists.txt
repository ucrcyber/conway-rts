cmake_minimum_required(VERSION 3.15)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")

add_executable(runAllTests
  Vector2.cpp
  LifeGrid.cpp
  StructureProperties.cpp
  Structure.cpp

  Event.cpp
  Client.cpp
  Team.cpp
)

target_link_libraries(runAllTests gmock gtest gtest_main libraries)
