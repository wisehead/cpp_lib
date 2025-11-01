/*******************************************************************************
 *      file name: 01.basic.cpp                                               
 *         author: hui chen. (c) 25                             
 *           mail: alex.chenhui@gmail.com                                        
 *   created time: 25/11/01-11:11                                    
 * modified time: 25/11/01-11:11                                    
 *******************************************************************************/
#include <iostream>

// 函数模板：交换两个任意类型的变量
template <typename T>  // 声明模板参数T（typename可替换为class）
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

int main() {
    int x = 1, y = 2;
    swap(x, y);  // 自动推导类型为int
    std::cout << x << " " << y << "\n";  // 输出：2 1

    double a = 3.14, b = 6.28;
    swap(a, b);  // 自动推导类型为double
    std::cout << a << " " << b << "\n";  // 输出：6.28 3.14

    return 0;
}
