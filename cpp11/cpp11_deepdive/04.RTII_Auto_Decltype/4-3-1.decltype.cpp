/*******************************************************************************
 *      file name: 4-3-1.decltype.cpp                                               
 *         author: Hui Chen. (c) 2020                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2020/09/21-15:58:13                              
 *  modified time: 2020/09/21-15:58:13                              
 *******************************************************************************/
#include <iostream>
#include <typeinfo>
using namespace std;
class White{};
class Black{};
int main() {
	White a;
	Black b;
	cout << typeid(a).name() << endl;    // 5White
	cout << typeid(b).name() << endl;    // 5Black
	White c;
	bool a_b_sametype = (typeid(a).hash_code() == typeid(b).hash_code());
	  bool a_c_sametype = (typeid(a).hash_code() == typeid(c).hash_code());
	  cout << "Same type? " << endl;
	  cout << "A and B? " << (int)a_b_sametype << endl;    // 0
	  cout << "A and C? " << (int)a_c_sametype << endl;    // 1
  }
  // 编译选项:g++ -std=c++11 4-3-1.cpp
