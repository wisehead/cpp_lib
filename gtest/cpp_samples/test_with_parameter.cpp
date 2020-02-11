/*******************************************************************************
 *      file name: test_with_parameter.cpp                                               
 *         author: Hui Chen. (c) 2020                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2020/02/11-21:45:42                              
 *  modified time: 2020/02/11-21:45:42                              
 *******************************************************************************/
#include<gtest/gtest.h>
// Returns true iff n is a prime number.
bool IsPrime(int n)
{
    // Trivial case 1: small numbers
    if (n <= 1) return false;
    // Trivial case 2: even numbers
    if (n % 2 == 0) return n == 2;
    // Now, we have that n is odd and n >= 3.
    // Try to divide n by every odd number i, starting from 3
    for (int i = 3; ; i += 2) {
        // We only have to try i up to the squre root of n
        if (i > n/i) break;
        // Now, we have i <= n/i < n.
        // If n is divisible by i, n is not prime.
        if (n % i == 0) return false;
    }
    // n has no integer factor in the range (1, n), and thus is prime.
    return true;
}
class IsPrimeParamTest : public::testing::TestWithParam<int>{};
TEST_P(IsPrimeParamTest, HandleTrueReturn)
{
 int n =  GetParam();
 EXPECT_TRUE(IsPrime(n));
}
//被测函数须传入多个相关的值
INSTANTIATE_TEST_CASE_P(TrueReturn, IsPrimeParamTest, testing::Values(3, 5, 11, 23, 17));
int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
