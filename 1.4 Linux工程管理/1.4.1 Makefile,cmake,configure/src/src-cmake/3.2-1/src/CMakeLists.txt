# 单个目录实现
# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)
# 工程
# PROJECT(0VOICE)
# 手动加入文件
SET(SRC_LIST main.c)
MESSAGE(STATUS "THIS IS BINARY DIR " ${PROJECT_BINARY_DIR})
MESSAGE(STATUS "THIS IS SOURCE DIR " ${PROJECT_SOURCE_DIR})

#设置子目录
set(SUB_DIR_LIST "${CMAKE_CURRENT_SOURCE_DIR}/dir1" "${CMAKE_CURRENT_SOURCE_DIR}/dir2")

foreach(SUB_DIR ${SUB_DIR_LIST})
    #遍历源文件
    aux_source_directory(${SUB_DIR} SRC_LIST)
    MESSAGE(STATUS "SUB_DIR-> " ${SUB_DIR})
    MESSAGE(STATUS "SRC_LIST-> " ${SRC_LIST})
endforeach()

# 添加头文件路径
INCLUDE_DIRECTORIES("dir1")
INCLUDE_DIRECTORIES("dir2")


ADD_EXECUTABLE(darren ${SRC_LIST} )


# 将执行文件安装到bin目录
INSTALL(TARGETS darren RUNTIME DESTINATION bin)