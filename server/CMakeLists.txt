project(uws-hello_world CXX)
cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 20)
set(SRCS main.cpp)

include_directories(${external_include_dirs})

add_executable(${PROJECT_NAME} ${SRCS})

# find_path(UWEBSOCKETS_INCLUDE_DIRS uwebsockets/App.h REQUIRED)
# target_include_directories(${PROJECT_NAME} PRIVATE ${UWEBSOCKETS_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} uWebSockets)
