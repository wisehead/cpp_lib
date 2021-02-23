#include "my_code_to_be_tested.h"

int My_class::return_num_bigger_than_10() {
    printf("I'm raw function\n");
    return 100;
}

int My_class::return_num_less_than_10() {
    printf("I'm raw function2\n");
    return 2;
}


int My_class::function_to_be_tested(int a) {
    if(return_num_bigger_than_10() < 10) {
        printf("Error 1\n");
        return -1;
    }
    if(return_num_less_than_10() > 10) {
        printf("Error 2\n");
        return -2;
    }
    return a;
}
