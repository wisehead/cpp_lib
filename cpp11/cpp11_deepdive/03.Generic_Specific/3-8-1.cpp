/*******************************************************************************
 *      file name: 3-8-1.cpp                                               
 *         author: Hui Chen. (c) 2020                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2020/09/07-17:00:06                              
 *  modified time: 2020/09/07-17:00:06                              
 *******************************************************************************/
#include <iostream>
using namespace std;
typedef unsigned char uint8;
struct RGBA{
    uint8 r;
    uint8 g;
    uint8 b;
    uint8 a;
    RGBA(uint8 R, uint8 G, uint8 B, uint8 A = 0):
        r(R), g(G), b(B), a(A){}
};
std::ostream & operator << (std::ostream & out, RGBA & col) {
    return out << "r: " << (int)col.r
        << ", g: " << (int)col.g
        << ", b: " << (int)col.b
        << ", a: " << (int)col.a << endl;
}
void blend(RGBA & col1, RGBA & col2){
    cout << "blend " << endl << col1 << col2 << endl;
}
int main() {
    RGBA col1(255, 240, 155);
    RGBA col2({15, 255, 10, 7});  // C++11风格的列表初始化
    blend(col1, col2);
}
// 编译选项:g++ -std=c++11 3-8-1.cpp
