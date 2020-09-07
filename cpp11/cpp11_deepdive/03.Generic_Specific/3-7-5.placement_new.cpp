/*******************************************************************************
 *      file name: 3-7-5.placement_new.cpp                                               
 *         author: Hui Chen. (c) 2020                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2020/09/07-16:45:30                              
 *  modified time: 2020/09/07-16:45:30                              
 *******************************************************************************/
#include <string>
using namespace std;
union T {
    string s;
    int n;
public:
    // 自定义构造函数和析构函数
    T(){ new (&s) string; }
    ~T() { s.~string(); }
};
int main() {
    T t;          // 构造析构成功
}
// 编译选项:g++ -std=c++11 3-7-5.cpp
