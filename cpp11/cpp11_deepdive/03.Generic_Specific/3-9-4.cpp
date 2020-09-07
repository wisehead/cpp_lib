/*******************************************************************************
 *      file name: 3-9-4.cpp                                               
 *         author: Hui Chen. (c) 2020                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2020/09/07-18:11:15                              
 *  modified time: 2020/09/07-18:11:15                              
 *******************************************************************************/
#include <iostream>
 using namespace std;
 namespace Jim {
 #if __cplusplus == 201103L
     inline
 #endif
     namespace cpp11{
             struct Knife{ Knife() { cout << "Knife in c++11." << endl; } };
             // ...
         }
     #if __cplusplus < 201103L
         inline
     #endif
         namespace oldcpp{
             struct Knife{ Knife() { cout << "Knife in old c++." << endl; } };
             // ...
         }
     }
     using namespace Jim;
     int main() {
         Knife a;              // Knife in c++11. (默认版本)
         cpp11::Knife b;      // Knife in c++11. (强制使用cpp11版本)
         oldcpp::Knife c;     // Knife in old c++. (强制使用oldcpp11版本)
     }
     // 编译选项:g++ -std=c++11 3-9-4.cpp
