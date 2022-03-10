cmake_minimum_required(VERSION 3.7.1)

project(hello-world)

set(SOURCE_FILES main.c)

message(STATUS "This is BINARY dir " ${PROJECT_BINARY_DIR})
#message(SEND_ERROR "darren is error")
message(STATUS "This is SOURCE dir " ${PROJECT_SOURCE_DIR})

add_executable(hello-world ${SOURCE_FILES})
ADD_EXECUTABLE(hello ${SOURCE_FILES})
