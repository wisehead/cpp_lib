./configure --prefix=/home/work/wangmengzhu/funcExp/bhook  
#��Ҫgcc44/48��gcc82����

make;make install

��3���������Զ�����ļ�Ϊso�ļ�

g++ -shared -rdynamic -o hook.so -fPIC wmzhook.cpp -I /home/work/wangmengzhu/funcExp/bhook/include

��4��������������

g++ main.cpp -o main

��5������֤
./main

bhook -u ./hook.so ./main
