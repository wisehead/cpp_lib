/*******************************************************************************
 *      file name: 3-11-2.cpp                                               
 *         author: Hui Chen. (c) 2020                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2020/09/07-18:29:46                              
 *  modified time: 2020/09/07-18:29:46                              
 *******************************************************************************/
template <int I> struct A {};
char xxx(int);
char xxx(float);
template <class T> A<sizeof(xxx((T)0))> f(T){}
int main() {
    f(1);
}
// 编译选项：g++ -std=c++11
