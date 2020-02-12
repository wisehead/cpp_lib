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

##2.4 Matcher
Matcher用于定义Mock类中的方法的形参的值（当然，如果你的方法不需要形参时，可以保持match为空。），它有以下几种类型：（更详细的介绍可以参见Google Mock Wiki上的Matcher介绍）
###2.4.1 通配符
| A | B | 
| ---- | ---- | 
| _ | 可以代表任意类型 | 
|A() or An() | 可以是type类型的任意值 | 

这里的_和*A*包括下面的那个匹配符都在Google Mock的*::testing*这个命名空间下，大家要用时需要先引入那个命名空间

###2.4.2 一般比较

| 操作符 | 备注 | 
| ---- | ---- | 
| Eq(value) 或者 value | argument == value，method中的形参必须是value | 
| Ge(value) | argument >= value，method中的形参必须大于等于value | 
| Gt(value) | argument > value | 
| Le(value) | argument <= value | 
| Lt(value) | argument < value |
| Ne(value) | argument != value |
| IsNull()	| method的形参必须是NULL指针 |
| NotNull() | argument is a non-null pointer |
| Ref(variable) | 形参是variable的引用 |
| TypedEq(value)	| 形参的类型必须是type类型，而且值必须是value|

###2.4.3 浮点数的比较

| 操作符 | 备注 | 
| ---- | ---- | 
| DoubleEq(a_double)	| 形参是一个double类型，比如值近似于a_double，两个NaN是不相等的 |
| FloatEq(a_float) | 同上，只不过类型是float
| NanSensitiveDoubleEq(a_double) | 形参是一个double类型，比如值近似于a_double，两个NaN是相等的，这个是用户所希望的方式
| NanSensitiveFloatEq(a_float) | 同上，只不过形参是float

###2.4.4 字符串匹配
这里的字符串即可以是C风格的字符串，也可以是C++风格的。

| 操作符 | 备注 | 
| ---- | ---- | 
| ContainsRegex(string) | 形参匹配给定的正则表达式
| EndsWith(suffix) | 形参以suffix截尾
| HasSubstr(string) |	形参有string这个子串
| MatchesRegex(string) |	从第一个字符到最后一个字符都完全匹配给定的正则表达式.
| StartsWith(prefix) |	形参以prefix开始
| StrCaseEq(string) |	参数等于string，并且忽略大小写
| StrCaseNe(string) |	参数不是string，并且忽略大小写
| StrEq(string) |	参数等于string
| StrNe(string) |	参数不等于string

### 2.4.5 容器的匹配
很多STL的容器的比较都支持==这样的操作，对于这样的容器可以使用上述的Eq(container)来比较。但如果你想写得更为灵活，可以使用下面的这些容器匹配方法：

| 操作符 | 备注 | 
| ---- | ---- | 
| Contains(e)	 | 在method的形参中，只要有其中一个元素等于e
| Each(e) |	参数各个元素都等于e
| ElementsAre(e0, e1, …, en) |	形参有n+1的元素，并且挨个匹配
| ElementsAreArray(array)或者ElementsAreArray(array, count) |	和ElementsAre()类似，除了预期值/匹配器来源于一个C风格数组
| ContainerEq(container) |	类型Eq(container)，就是输出结果有点不一样，这里输出结果会带上哪些个元素不被包含在另一个容器中
| Pointwise(m, container)

###2.4.6 MockFoo.h
上述的一些匹配器都比较简单，我就随便打包举几最简单的例子演示一下吧： 我稍微修改一下之前的Foo.h和MockFoo.h， MockFoo.h 增加了2个方法

```cpp
#ifndef MOCKFOO_H_
#define MOCKFOO_H_
 
#include <gmock/gmock.h>
#include <string>
#include <vector>
#include "FooInterface.h"
 
namespace seamless {
 
class MockFoo: public FooInterface {
public:
        MOCK_METHOD0(getArbitraryString, std::string());
        MOCK_METHOD1(setValue, void(std::string& value));
        MOCK_METHOD2(setDoubleValues, void(int x, int y));
};
 
}  // namespace seamless
 
#endif // MOCKFOO_H_
```

###2.4.7 FooMain.h

```cpp
#include <cstdlib>
#include <gmock/gmock.h>
#include <iostream>
#include <string>
 
#include "MockFoo.h"
 
using namespace seamless;
using namespace std;
 
using ::testing::Assign;
using ::testing::Eq;
using ::testing::Ge;
using ::testing::Return;
 
int main(int argc, char** argv) {
        ::testing::InitGoogleMock(&argc, argv);
 
        string value = "Hello World!";
        MockFoo mockFoo;
 
        EXPECT_CALL(mockFoo, setValue(testing::_));
        mockFoo.setValue(value);
 
        // 这里我故意犯错
        EXPECT_CALL(mockFoo, setDoubleValues(Eq(1), Ge(1)));
        mockFoo.setDoubleValues(1, 0);
 
        return EXIT_SUCCESS;
}
```
第22行，让setValue的形参可以传入任意参数
另外，我在第26~27行故意犯了个错（为了说明上述这些匹配器的作用），我之前明明让setDoubleValues第二个参数得大于等于1,但我实际传入时却传入一个0。这时程序运行时就报错了：
