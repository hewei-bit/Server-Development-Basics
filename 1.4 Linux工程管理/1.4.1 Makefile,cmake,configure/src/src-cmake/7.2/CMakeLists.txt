
# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)
PROJECT(0VOICE)

ADD_SUBDIRECTORY(src bin)
SET(RELEASE_DIR ${PROJECT_SOURCE_DIR}/release)
#INSTALL(FILES COPYRIGHT README DESTINATION share/doc/cmake/0voice)
INSTALL(DIRECTORY doc/ DESTINATION share/doc/cmake/0voice)