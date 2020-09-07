/*******************************************************************************
 *      file name: 3-9-3.cpp                                               
 *         author: Hui Chen. (c) 2020                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2020/09/07-18:05:45                              
 *  modified time: 2020/09/07-18:05:45                              
 *******************************************************************************/
#include <iostream>
using namespace std;
namespace Jim {
      inline namespace Basic {
          struct Knife{ Knife() { cout << "Knife in Basic." << endl; } };
          class CorkScrew{};
      }
      inline namespace Toolkit {
          template<typename T> class SwissArmyKnife{};
      }
      // ...
      namespace Other{
          Knife b;               // Knife in Basic
          struct Knife{ Knife() { cout << "Knife in Other" << endl;} };
          Knife c;               // Knife in Other
          Basic::Knife k;      // Knife in Basic
      }
  }
  // 这是LiLei在使用Jim的库
  namespace Jim {
      template<> class SwissArmyKnife<Knife>{};    // 编译通过
  }
  using namespace Jim;
  int main() {
      SwissArmyKnife<Knife> sknife;
  }
  // 编译选项:g++ -std=c++11 3-9-3.cpp
