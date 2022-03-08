
# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)
PROJECT(0VOICE)

# 添加子目录
ADD_SUBDIRECTORY(src)

#INSTALL(FILES COPYRIGHT README DESTINATION share/doc/cmake/0voice)
# 安装doc到  share/doc/cmake/0voice目录
# 默认/usr/local/
#指定自定义目录，比如 cmake -DCMAKE_INSTALL_PREFIX=/tmp/usr ..
INSTALL(DIRECTORY doc/ DESTINATION share/doc/cmake/0voice)
#INSTALL(TARGETS darren RUNTIME DESTINATION bin)