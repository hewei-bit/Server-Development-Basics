#编译步骤
(1)创建build目录
mkdir build
(2)进入build目录
cd build
(3)编译debug版本
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
生成的执行文件和库在 /release/linux/Debug
(3)编译release版本
cmake -DCMAKE_BUILD_TYPE=Release ..
make
生成的执行文件和库在 /release/linux/Release

# 说明
Debug版会使用参数-g；Release版使用-O3 –DNDEBUG

