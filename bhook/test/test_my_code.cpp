#include "fault.h"
#include "stdio.h"
#include "my_code_to_be_tested.h"
#include <gtest/gtest.h>
#include "mock_my_code.h"
#include "fault_wrapper.h"


class My_code_tests : public ::testing::Test {
    public:
        void SetUp() {
            printf("Before test\n");
            //TODO:init work
        }
        void TearDown() {
            printf("After test\n");
            //TODO:clean work
        }
    private:
};


TEST_F(My_code_tests, test1) {
    AttachStatic add_bigger_hook("My_class::return_num_bigger_than_10", (void *)mock_my_class_return_num_bigger_than_10);
    AttachStatic add_less_hook("My_class::return_num_less_than_10", (void *)mock_my_class_return_num_less_than_10);

    My_class *my = new My_class;

    my->function_to_be_tested(1);
    EXPECT_EQ(1, my->function_to_be_tested(1));

    add_bigger_hook.Enable(1);
    EXPECT_EQ(-1, my->function_to_be_tested(1));

    add_bigger_hook.Disable();
    add_less_hook.Enable(100);
    EXPECT_EQ(-2, my->function_to_be_tested(1));

    delete my;

}


int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    testing::GTEST_FLAG(color) = "yes";
    int ret = RUN_ALL_TESTS();
    fault_release();
    return ret;
}
