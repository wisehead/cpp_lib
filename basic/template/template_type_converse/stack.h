/*******************************************************************************
 *      file name: stack.h                                               
 *         author: Hui Chen. (c) 2020                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2020/08/19-11:12:49                              
 *  modified time: 2020/08/19-11:12:49                              
 *******************************************************************************/
//statck.h
template <class T> class Stack {
    public:
        Stack();
        ~Stack();
        void push(T t);
        T pop();
        bool isEmpty();
        template<class T2>  operator Stack<T2>();
    private:
        T *m_pT;        
        int m_maxSize;
        int m_size;
};

#include "stack.cpp"
