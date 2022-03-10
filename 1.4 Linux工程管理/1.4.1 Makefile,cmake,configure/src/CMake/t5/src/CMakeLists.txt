CMAKE_MINIMUM_REQUIRED(VERSION 2.8.4)

ADD_EXECUTABLE(curltest main.c)

#include_directories(/usr/local/include)
#target_link_libraries(curltest curl)

FIND_PACKAGE(CURL)

if(CURL_FOUND)
  INCLUDE_DIRECTORIES(${CURL_INCLUDE_DIR})
  TARGET_LINK_LIBRARIES(curltest ${CURL_LIBRARY})
else(CURL_FOUND)
  MESSAGE(FATAL_ERROR "CURL library not found")
endif(CURL_FOUND)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
