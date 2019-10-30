/*******************************************************************************
 *      file name: thread_local.cpp                                               
 *         author: Hui Chen. (c) 2019                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2019/10/30-10:36:29                              
 *  modified time: 2019/10/30-10:36:29                              
 *******************************************************************************/
#include <iostream>
#include <future>
#include <vector>
#include <chrono>
#include <random>
using namespace std;
using namespace chrono;

thread_local default_random_engine dre;

vector<int> test_dre(int seed)
{
    dre.seed(seed);
    int vecSize = 10;
    vector<int> temp(vecSize);
    for (int i = 0; i < vecSize; ++i)
    {
        temp[i] = dre();
        this_thread::sleep_for(milliseconds(100));
    }
    return temp;
}

bool equal(const vector<int> &v1, const vector<int> &v2)
{
    int size1 = v1.size();
    int size2 = v2.size();
    if (size1 != size2)
        return false;

    for (int i = 0; i < size1; ++i)
    {
        if (v1[i] != v2[i])
            return false;
    }
    return true;
}

int main()
{
    int numThread = 2;
    using returnType = vector<int>;

    future<returnType> future1 = async(test_dre, 0);
    returnType result2 = test_dre(0);
    returnType result1 = future1.get();

    if (equal(result1, result2))
        cout << "they are equal" << endl;
    else
        cout << "they are not equal" << endl;

    system("pause");
    return 0;
}
