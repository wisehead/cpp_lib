/*******************************************************************************
 *      file name: 3-10-1.is_same.cpp                                               
 *         author: Hui Chen. (c) 2020                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2020/09/07-18:17:25                              
 *  modified time: 2020/09/07-18:17:25                              
 *******************************************************************************/
#include <iostream>
#include <type_traits>
using namespace std;
using uint = unsigned int;
typedef unsigned int UINT;
using sint = int;
int main() {
    cout << is_same<uint, UINT>::value << endl; // 1
}
// 编译选项:g++ -std=c++11 3-10-1.cpp
