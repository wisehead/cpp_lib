thread_local变量是C++ 11新引入的一种存储类型。它会影响变量的存储周期(Storage duration)，C++中有4种存储周期：

automatic
static
dynamic
thread
有且只有thread_local关键字修饰的变量具有线程周期(thread duration)，这些变量(或者说对象）在线程开始的时候被生成(allocated)，在线程结束的时候被销毁(deallocated)。并且每 一个线程都拥有一个独立的变量实例(Each thread has its own instance of the object)。thread_local 可以和static 与 extern关键字联合使用，这将影响变量的链接属性(to adjust linkage)。
那么，哪些变量可以被声明为thread_local？以下3类都是ok的

命名空间下的全局变量
类的static成员变量
本地变量（方法或者函数中的变量）
下面引用《C++ Concurrency in Action》书中的例子来说明这3种情况：

thread_local int x;  //A thread-local variable at namespace scope
class X
{
    static thread_local std::string s; //A thread-local static class data member
};
static thread_local std::string X::s;  //The definition of X::s is required

void foo()
{
    thread_local std::vector<int> v;  //A thread-local local variable
}
1
2
3
4
5
6
7
8
9
10
11
既然每个线程都拥有一份独立的thread_local变量，那么就有2个问题需要考虑：

各线程的thread_local变量是如何初始化的
各线程的thread_local变量在初始化之后拥有怎样的生命周期，特别是被声明为thread_local的本地变量(local variables)
下面的代码可以帮助回答这2个问题，我的测试环境是vs2015。

输出的前3行打印能帮助解答thread_local变量是如何初始化的，可以看到每个线程都会进行一次初始化，例子中的g_n在主线程中最早被初始化为1，随后被修改为2和3，但这些修改操作并不影响g_n在线程t1和t2中的初始值(值为1)，虽然t2和t3线程启动的时候主线程中的变量值已经被更新为3，所以主线程、thread1、thread2打印结果分别为3，2，2。（thread_local声明的变量在主线程、线程t1和线程t2中都相互独立）

后6行打印说明了一个事实，声明为thread_local的本地变量在线程中是持续存在的，不同于普通临时变量的生命周期，它具有static变量一样的初始化特征和生命周期，虽然它并没有被声明为static。例子中foo函数中的thread_local变量 i 在每个线程第一次执行到的时候初始化，在每个线程各自累加，在线程结束时释放。
