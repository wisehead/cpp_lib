/*******************************************************************************
 *      file name: 4-2-13.cpp                                               
 *         author: Hui Chen. (c) 2020                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2020/09/07-19:43:12                              
 *  modified time: 2020/09/07-19:43:12                              
 *******************************************************************************/
#include <vector>
using namespace std;
void fun(auto x =1){}  // 1: auto函数参数，无法通过编译
struct str{
    auto var = 10;    // 2: auto非静态成员变量，无法通过编译
};
int main() {
    char x[3];
    auto y = x;
    auto z[3] = x; // 3: auto数组，无法通过编译
    // 4: auto模板参数（实例化时），无法通过编译
    vector<auto> v = {1};
}
// 编译选项:g++ -std=c++11 4-2-13.cpp
