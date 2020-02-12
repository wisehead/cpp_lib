./configure --prefix=/home/work/wangmengzhu/funcExp/bhook  
#需要gcc44/48，gcc82不行

make;make install

（3）、编译自定义的文件为so文件

g++ -shared -rdynamic -o hook.so -fPIC wmzhook.cpp -I /home/work/wangmengzhu/funcExp/bhook/include

（4）、编译主函数

g++ main.cpp -o main

（5）、验证
./main

bhook -u ./hook.so ./main
