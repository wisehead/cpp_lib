/*******************************************************************************
 *      file name: test2.cpp                                               
 *         author: Hui Chen. (c) 2020                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2020/08/19-12:03:16                              
 *  modified time: 2020/08/19-12:03:16                              
 *******************************************************************************/
class Util {
    public:
         template <class T> static bool equal(T t1, T t2) {
            return t1 == t2;
        }
};

int main() {
    int a = 1, b = 2;
    Util::equal<int>(1, 2);
    return 0;
}
