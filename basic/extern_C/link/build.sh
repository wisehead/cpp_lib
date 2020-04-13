#############################################################
#   File Name: build.sh
#     Autohor: Hui Chen (c) 2020
#        Mail: chenhui13@baidu.com
# Create Time: 2020/04/13-22:03:32
#############################################################
#!/bin/sh 
gcc -c f1.c -o f1.o
gcc -c test.cpp -o test.o
gcc test.o f1.o
