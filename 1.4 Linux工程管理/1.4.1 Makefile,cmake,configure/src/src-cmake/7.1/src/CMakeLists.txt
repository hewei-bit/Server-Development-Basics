# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)


# 设置release版本还是debug版本
if(${CMAKE_BUILD_TYPE} MATCHES "Release")
    message(STATUS "Release版本")
    set(BuildType "Release")
    MESSAGE(STATUS "CXXFLAGS: " ${CMAKE_CXX_FLAGS})
    MESSAGE(STATUS "CFLAGS: " ${CMAKE_C_FLAGS})
else()
    set(BuildType "Debug")
    message(STATUS "Debug版本")
    SET(CMAKE_C_FLAGS "$ENV{CFLAGS} -O0 -g")
    MESSAGE(STATUS "CXXFLAGS: " ${CMAKE_CXX_FLAGS})  # 默认没有写参数
    MESSAGE(STATUS "CFLAGS: " ${CMAKE_C_FLAGS})
endif()

#设置生成的so动态库最后输出的路径
#设置bin和lib库目录
SET(RELEASE_DIR ${PROJECT_SOURCE_DIR}/release)
#设置bin和lib库目录
# debug和release版本目录不一样
SET(LIBRARY_OUTPUT_PATH ${RELEASE_DIR}/linux/${BuildType})
SET(EXECUTABLE_OUTPUT_PATH ${RELEASE_DIR}/linux/${BuildType})
add_compile_options(-fPIC)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)
# 添加头文件路径
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/dir1")
# 添加 dir1 子目录
add_subdirectory(dir1)
# 添加头文件路径
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/dir2")
# 添加 dir2 子目录
add_subdirectory(dir2)


# 指定生成目标
add_executable(multi-dir main.c)
# 添加链接库
target_link_libraries(multi-dir Dir1 Dir2)
# 将执行文件安装到bin目录
INSTALL(TARGETS multi-dir RUNTIME DESTINATION bin)