        #include <iostream>
        using namespace std;
        int main() {
            int arr[5] = { 1, 2, 3, 4, 5 };
            for (int & e: arr)
                e *= 2;
            for (int & e: arr)
                cout << e << '\t';
        }
        // 编译选项:g++ -std=c++11 4-5-3.cpp
