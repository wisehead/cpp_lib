#一、Google Mock概述
Google Mock（简称gmock）是Google在2008年推出的一套针对C++的Mock框架，它灵感取自于jMock、EasyMock、harcreat。它提供了以下这些特性：

轻松地创建mock类
支持丰富的匹配器（Matcher）和行为（Action）
支持有序、无序、部分有序的期望行为的定义
多平台的支持

#二、Google Mock使用
##2.1 最简单的例子

我比较喜欢举例来说明这些个、那些个玩意，因此我们先来看看Google Mock就简单的用法和作用。

首先，那个懒惰的同学已经定义好了这么一个接口（万幸，他至少把接口定义好了）：
###2.1.1 FooInterface.h

```cpp
#ifndef FOOINTERFACE_H_
#define FOOINTERFACE_H_
 
#include <string>
 
namespace seamless {
 
class FooInterface {
public:
        virtual ~FooInterface() {}
 
public:
        virtual std::string getArbitraryString() = 0;
};
 
}  // namespace seamless
 
#endif // FOOINTERFACE_H_
```
这里需要注意几点：
FooInterface的析构函数~FooInterface()必须是virtual的
在第13行，我们得把getArbitraryString定义为纯虚函数。其实getArbitraryString()也不一定得是纯虚函数，这点我们后面会提到.

###2.1.2 FooMock.h

```cpp
#ifndef MOCKFOO_H_
#define MOCKFOO_H_
 
#include <gmock/gmock.h>
#include <string>
#include "FooInterface.h"
 
namespace seamless {
 
class MockFoo: public FooInterface {
public:
        MOCK_METHOD0(getArbitraryString, std::string());
};
 
}  // namespace seamless
 
#endif // MOCKFOO_H_
```
* 第10行我们的MockFoo类继承懒同学的FooInterface
* 第22行我们定义使用gmock中的一个宏（Macro）MOCK_METHOD0来定义MockFoo中的getArbitraryString。Google Mock是需要你根据不同的形参个数来使用不同的Mock Method，我这里getArbitraryString没有函数，就是MOCK_METHOD0了，同理，如果是一个形参，就是MOCK_METHOD1了，以此往下。

###2.1.3 FooMain.cc

```cpp
#include <cstdlib>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iostream>
#include <string>
 
#include "MockFoo.h"
 
using namespace seamless;
using namespace std;
 
using ::testing::Return;
 
int main(int argc, char** argv) {
        ::testing::InitGoogleMock(&argc, argv);
 
        string value = "Hello World!";
        MockFoo mockFoo;
        EXPECT_CALL(mockFoo, getArbitraryString()).Times(1).
                WillOnce(Return(value));
        string returnValue = mockFoo.getArbitraryString();
        cout << "Returned Value: " << returnValue << endl;
 
        return EXIT_SUCCESS;
}
```

最后我们运行编译，得到的结果如下：

> Returned Value: Hello World!

在这里：
* 第15行，初始化一个Google Mock
* 第18行，声明一个MockFoo的对象：mockFoo
* 第19行，是为MockFoo的getArbitraryString()方法定义一个期望行为，其中Times(1)的意思是运行一次，WillOnce(Return(value))的意思是第一次运行时把value作为getArbitraryString()方法的返回值。
这就是我们最简单的使用Google Mock的例子了，使用起来的确比较简便吧。

##2.2 典型的流程

通过上述的例子，已经可以看出使用Mock类的一般流程如下：

* 引入你要用到的Google Mock名称. 除宏或其它特别提到的之外所有Google Mock名称都位于*testing*命名空间之下.
* 建立模拟对象(Mock Objects).
* 可选的,设置模拟对象的默认动作.
* 在模拟对象上设置你的预期(它们怎样被调用,应该怎样回应?).

##2.3 自定义方法/成员函数的期望行为
从上述的例子中可以看出，当我们针对懒同学的接口定义好了Mock类后，在单元测试/主程序中使用这个Mock类中的方法时最关键的就是对期望行为的定义。
对方法期望行为的定义的语法格式如下：

> EXPECT_CALL(mock_object, method(matcher1, matcher2, ...))
>     .With(multi_argument_matcher)
>     .Times(cardinality)
>     .InSequence(sequences)
>     .After(expectations)
>     .WillOnce(action)
>     .WillRepeatedly(action)
>     .RetiresOnSaturation();

解释一下这些参数（虽然很多我也没弄明白）：
* 第1行的mock_object就是你的Mock类的对象
* 第1行的method(matcher1, matcher2, …)中的method就是你Mock类中的某个方法名，比如上述的getArbitraryString;而matcher（匹配器）的意思是定义方法参数的类型，我们待会详细介绍。
* 第3行的Times(cardinality)的意思是之前定义的method运行几次。至于cardinality的定义，我也会在后面详细介绍。
* 第4行的InSequence(sequences)的意思是定义这个方法被执行顺序（优先级），我会再后面举例说明。
* 第6行WillOnce(action)是定义一次调用时所产生的行为，比如定义该方法返回怎么样的值等等。
* 第7行WillRepeatedly(action)的意思是缺省/重复行为。

我稍微先举个例子来说明一下，后面有针对更为详细的说明：

	EXPECT_CALL(mockTurtle, getX()).Times(testing::AtLeast(5)).
	                WillOnce(testing::Return(100)).WillOnce(testing::Return(150)).
	                WillRepeatedly(testing::Return(200))

这个期望行为的定义的意思是：

* 调用mockTurtle的getX()方法
* 这个方法会至少调用5次
* 第一次被调用时返回100
* 第2次被调用时返回150
* 从第3次被调用开始每次都返回200