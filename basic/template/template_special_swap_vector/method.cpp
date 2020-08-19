/*******************************************************************************
 *      file name: method.cpp                                               
 *         author: Hui Chen. (c) 2020                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2020/08/19-11:03:46                              
 *  modified time: 2020/08/19-11:03:46                              
 *******************************************************************************/
#include <vector>
using namespace std;
template<class T> void swap(T& t1, T& t2) {
    T tmpT;
    tmpT = t1;
    t1 = t2;
    t2 = tmpT;
}

/*
template<> void swap(std::vector<int>& t1, std::vector<int>& t2) {
    t1.swap(t2);
}
*/

template<class V> void swap(std::vector<V>& t1, std::vector<V>& t2) {
   t1.swap(t2);
}
