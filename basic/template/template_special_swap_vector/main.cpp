/*******************************************************************************
 *      file name: main.cpp                                               
 *         author: Hui Chen. (c) 2020                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2020/08/19-11:04:12                              
 *  modified time: 2020/08/19-11:04:12                              
 *******************************************************************************/
//main.cpp
#include <stdio.h>
#include <vector>
#include <string>
#include "method.h"
int main() {
    using namespace std;
    //模板方法 
    string str1 = "1", str2 = "2";
    swap(str1, str2);
    printf("str1:%s, str2:%s\n", str1.c_str(), str2.c_str());  
    
    vector<int> v1, v2;
    v1.push_back(1);
    v2.push_back(2);
    swap(v1, v2);
    for (int i = 0; i < v1.size(); i++) {
        printf("v1[%d]:%d\n", i, v1[i]);
    }
    for (int i = 0; i < v2.size(); i++) {
        printf("v2[%d]:%d\n", i, v2[i]);
    }
    return 0;
}
