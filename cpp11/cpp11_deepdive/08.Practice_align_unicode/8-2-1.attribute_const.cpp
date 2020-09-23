          extern int area(int n) __attribute__((const));
          int main() {
              int i;
              int areas = 0;
              for (i = 0; i < 10; i++) {
                  areas += area(3) * i;
              }
          }
        // 编译选项:g++ -c 8-2-1.cpp
