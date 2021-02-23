#############################################################
#   File Name: build.sh
#     Autohor: Hui Chen (c) 2020
#        Mail: chenhui13@baidu.com
# Create Time: 2020/02/12-15:32:18
#############################################################
#!/bin/sh 
g++ -std=c++11 -g -o out -I. -lgtest -lgmock -lpthread Rank.cpp tester.cpp
