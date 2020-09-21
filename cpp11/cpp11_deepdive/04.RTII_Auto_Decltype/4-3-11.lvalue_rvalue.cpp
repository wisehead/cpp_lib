        #include <type_traits>
        #include <iostream>
        using namespace std;
        int i = 4;
        int arr[5] = {0};
        int *ptr = arr;
        int && RvalRef();
        int main(){
            cout << is_rvalue_reference<decltype(RvalRef())>::value << endl;       // 1
            cout << is_lvalue_reference<decltype(true ? i : i)>::value << endl; // 1
            cout << is_lvalue_reference<decltype((i))>::value << endl;             // 1
            cout << is_lvalue_reference<decltype(++i)>::value << endl;             // 1
            cout << is_lvalue_reference<decltype(arr[3])>::value << endl;          // 1
            cout << is_lvalue_reference<decltype(*ptr)>::value << endl;            // 1
            cout << is_lvalue_reference<decltype("lval")>::value << endl;          // 1
            cout << is_lvalue_reference<decltype(i++)>::value << endl;             // 0
            cout << is_rvalue_reference<decltype(i++)>::value << endl;             // 0
        }
        // 编译选项:g++ -std=c++11 4-3-11.cpp
