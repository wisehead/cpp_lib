#include<iostream>
using namespace std;
        int main() {
            int girls = 3, boys = 4;
            auto totalChild = [](int x, int y)->int{ return x + y; };
            int x = totalChild(girls, boys);
			cout<<"x:"<<x<<endl;
            return x;
        }
        //编译选项: g++ -std=c++11 7-3-1.cpp
