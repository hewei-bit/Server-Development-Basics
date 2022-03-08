# 设置release版本还是debug版本
if(${CMAKE_BUILD_TYPE} MATCHES "Release")
    message(STATUS "Release版本")
    set(BuildType "Release")
    MESSAGE(STATUS "CXXFLAGS: " ${CMAKE_CXX_FLAGS})
    MESSAGE(STATUS "CFLAGS: " ${CMAKE_C_FLAGS})
else()
    set(BuildType "Debug")
    message(STATUS "Debug版本")
    MESSAGE(STATUS "CXXFLAGS: " ${CMAKE_CXX_FLAGS})
    MESSAGE(STATUS "CFLAGS: " ${CMAKE_C_FLAGS})
endif()

#设置lib库目录
set(RELEASE_DIR ${PROJECT_SOURCE_DIR}/release)
# debug和release版本目录不一样
#设置生成的so动态库最后输出的路径
SET(LIBRARY_OUTPUT_PATH ${RELEASE_DIR}/linux/${BuildType})
add_compile_options(-fPIC)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS 变量
aux_source_directory(. DIR_LIB_SRCS)
# 生成链接库Dir2
#add_library (libDir2.a STATIC  ${DIR_LIB_SRCS})
# 生成动态库
add_library (Dir2 SHARED  ${DIR_LIB_SRCS})
# 将库文件安装到lib目录
INSTALL(TARGETS Dir2 DESTINATION lib)
# 将头文件include
INSTALL(FILES dir2.h DESTINATION include) 
