/*******************************************************************************
 *      file name: test1.cpp                                               
 *         author: Hui Chen. (c) 2020                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2020/08/19-12:02:40                              
 *  modified time: 2020/08/19-12:02:40                              
 *******************************************************************************/
class Util {
    public:
        template <class T> bool equal(T t1, T t2) {
            return t1 == t2;
        }
};

int main() {
    Util util;
    int a = 1, b = 2;
    util.equal<int>(1, 2);
    return 0;
}
