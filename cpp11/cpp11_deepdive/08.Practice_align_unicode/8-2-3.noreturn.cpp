        void DoSomething1();
        void DoSomething2();
        [[ noreturn ]] void ThrowAway() {
            throw "expection"; // 控制流跳转到异常处理
        }
        void Func(){
            DoSomething1();
            ThrowAway();
            DoSomething2(); // 该函数不可到达
        }
        // 编译选项:clang++ -std=c++11-c 8-2-3.cpp
