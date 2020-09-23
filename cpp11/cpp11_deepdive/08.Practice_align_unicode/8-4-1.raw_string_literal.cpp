        #include <iostream>
        using namespace std;
        int main(){
            cout << R"(hello,\n
                  world)" << endl;
            return 0;
        }
        //编译选项: g++ 8-1-2.cpp -std=c++11
