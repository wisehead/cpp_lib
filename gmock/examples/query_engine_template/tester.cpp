/*******************************************************************************
 *      file name: tester.cpp                                               
 *         author: Hui Chen. (c) 2020                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2020/02/12-15:05:52                              
 *  modified time: 2020/02/12-15:05:52                              
 *******************************************************************************/
#include <boost/cstdint.hpp>
#include <boost/shared_ptr.hpp>
#include <cstdlib>
#include <gmock/gmock.h>
 
#include "MockIAPIProviderInterface.h"
#include "MockIParameterInterface.h"
#include "Rank.h"
 
using namespace seamless;
using namespace std;
 
using ::testing::_;
using ::testing::AtLeast;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgumentPointee;
 
int main(int argc, char** argv) {
        ::testing::InitGoogleMock(&argc, argv);
 
        MockIAPIProviderInterface* iAPIProvider = new MockIAPIProviderInterface;
 
        InSequence dummy;
        EXPECT_CALL(*iAPIProvider, queryInterface(_)).Times(AtLeast(1)).
                WillRepeatedly(Return(1));
 
        Rank rank;
        rank.processQuery(iAPIProvider);
 
        delete iAPIProvider;
 
        return EXIT_SUCCESS;
}