/*******************************************************************************
 *      file name: 3-8-3_Watt.cpp                                               
 *         author: Hui Chen. (c) 2020                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2020/09/07-17:09:21                              
 *  modified time: 2020/09/07-17:09:21                              
 *******************************************************************************/
struct Watt{ unsigned int v; };
Watt operator "" _w(unsigned long long v) {
    return {(unsigned int)v};
}

int main() {
    Watt capacity = 1024_w;
}
// 编译选项:g++ -std=c++11 3-8-3.cpp
