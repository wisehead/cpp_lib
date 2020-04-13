#############################################################
#   File Name: build.sh
#     Autohor: Hui Chen (c) 2020
#        Mail: chenhui13@baidu.com
# Create Time: 2020/04/13-21:57:11
#############################################################
#!/bin/sh 
gcc -S f1.c
gcc -S f1_no_extern.cpp
gcc -S f1_extern.cpp
