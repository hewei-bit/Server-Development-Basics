cmake_minimum_required(VERSION 2.8s)
# 设置release版本还是debug版本
if(${CMAKE_BUILD_TYPE} MATCHES "Release")
    MESSAGE(STATUS "Release版本")
    SET(BuildType "Release")
else()
    SET(BuildType "Debug")
    MESSAGE(STATUS "Debug版本")
endif()

#设置lib库目录
SET(RELEASE_DIR ${PROJECT_SOURCE_DIR}/release)
# debug和release版本目录不一样
#设置生成的so动态库最后输出的路径
#SET(LIBRARY_OUTPUT_PATH ${RELEASE_DIR}/linux/${BuildType})
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/${BuildType})
ADD_COMPILE_OPTIONS(-fPIC)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS 变量
AUX_SOURCE_DIRECTORY(. DIR_LIB_SRCS)
# 默认生成静态库链接库Dir1
#ADD_LIBRARY (Dir1 ${DIR_LIB_SRCS})
# SHARED生成动态库
ADD_LIBRARY (Dir1 SHARED  ${DIR_LIB_SRCS})