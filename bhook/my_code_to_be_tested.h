#ifndef _MY_CLASS_H_
#define _MY_CLASS_H_



#include "stdio.h"

class My_class {
    public:
        int function_to_be_tested(int a);
    private:
        int return_num_bigger_than_10();
        int return_num_less_than_10();
};

#endif
