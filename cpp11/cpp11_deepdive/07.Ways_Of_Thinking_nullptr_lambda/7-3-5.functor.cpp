          class _functor {
          public:
              int operator()(int x, int y) { return x + y; }
          };
          int main(){
              int girls = 3, boys = 4;
              _functor totalChild;
              return totalChild(5, 6);
          }
          // 编译选项:g++ 7-3-5.cpp -std=c++11
