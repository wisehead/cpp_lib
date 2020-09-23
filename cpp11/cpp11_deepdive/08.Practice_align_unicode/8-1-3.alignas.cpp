        #include <iostream>
        using namespace std;
        // 自定义的ColorVector，对齐到32字节的边界
        struct alignas(32) ColorVector {
              double r;
              double g;
              double b;
              double a;
          };
          int main() {
              // 使用C++11中的alignof来查询ColorVector的对齐方式
              cout << "alignof(ColorVector): " << alignof(ColorVector) << endl;
              return 1;
          }
          // 编译选项:g++ -std=c++11 8-1-3.cpp
