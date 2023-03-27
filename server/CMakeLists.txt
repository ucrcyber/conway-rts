project(uws-hello_world CXX)
cmake_minimum_required(VERSION 3.15)

# this cmake modified from https://github.com/Rubonnek/uWebSockets-cmake-example/blob/master/CMakeLists.txt

set(UWS_APP_H
	${UWEBSOCKETS_DIRECTORY}/App.h
	${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/uwebsockets-src/uSockets/src/libusockets.h
)

set(SRCS main.cpp)

add_executable(${PROJECT_NAME} ${SRCS} ${UWS_APP_H})
target_include_directories(${PROJECT_NAME} PRIVATE ${UWEBSOCKETS_DIRECTORY})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/uwebsockets-src/uSockets/src)

set(SINGLE_THREAD_ECHO_SHARED_LIBRARIES
	ssl
	crypto
	uv
	uWS
	z
)

target_link_libraries(${PROJECT_NAME} ${SINGLE_THREAD_ECHO_SHARED_LIBRARIES})
