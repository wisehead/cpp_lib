#include <stdio.h>
#include "fault.h"
#include "mock_my_code.h"

int mock_my_class_return_num_bigger_than_10(My_class *my) {

    int err, ret;

    ret = fault_fail("My_class::return_num_bigger_than_10", &err, NULL);
    if (ret == 0) {
        printf("I'm mock function\n");
        return err;
    } else {
        using REAL_FUNC = int (*)(My_class*);
        REAL_FUNC real_func = (REAL_FUNC)get_real_func_lib((char *)"My_class::return_num_bigger_than_10");
        return real_func(my);
    }

    return -1;
}

int mock_my_class_return_num_less_than_10(My_class *my) {

    int err, ret;

    ret = fault_fail("My_class::return_num_less_than_10", &err, NULL);
    if (ret == 0) {
        printf("I'm mock function2\n");
        return err;
    } else {
        using REAL_FUNC = int (*)(My_class*);
        REAL_FUNC real_func = (REAL_FUNC)get_real_func_lib((char *)"My_class::return_num_less_than_10");
        return real_func(my);
    }

    return -1;
}
