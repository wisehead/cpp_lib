/*******************************************************************************
 *      file name: 3-7-6_union_like_class.cpp                                               
 *         author: Hui Chen. (c) 2020                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2020/09/07-16:53:12                              
 *  modified time: 2020/09/07-16:53:12                              
 *******************************************************************************/
#include <cstring>
using namespace std;
struct Student{
    Student(bool g, int a): gender(g), age(a){}
    bool gender;
    int age;
};
class Singer {
public:
    enum Type {STUDENT, NATIVE, FOREIGNER};
    Singer(bool g, int a): s(g, a) { t = STUDENT; }
    Singer(int i): id(i) { t = NATIVE; }
    Singer(const char* n, int s) {
        int size = (s > 9) ? 9 : s;
        memcpy(name, n, size);
        name[s] = '\0';
        t = FOREIGNER;
    }
    ~Singer() {}
private:
    Type t;
    union {      // 匿名的非受限联合体
        Student s;
        int id;
        char name[10];
    };
};

int main(){
	Singer(true, 13);
	Singer(310217);
	Singer("J Michael", 9);
}
// 编译选项:g++ -std=c++11 3-7-6.cpp
