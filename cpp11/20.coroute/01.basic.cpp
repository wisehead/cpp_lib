#include <iostream>
#include <coroutine>
#include <future>
#include <thread>
#include <chrono>

// 协程返回类型：task（用于无返回值的协程）
struct task {
    // 协程承诺类型（必须定义）
    struct promise_type {
        task get_return_object() { 
            return task{std::coroutine_handle<promise_type>::from_promise(*this)}; 
        }
        std::suspend_never initial_suspend() { return {}; } // 不暂停，立即执行
        std::suspend_never final_suspend() noexcept { return {}; } // 结束不暂停
        void return_void() {} // 处理 co_return;
        void unhandled_exception() { std::terminate(); } // 处理异常
    };

    std::coroutine_handle<promise_type> handle;
    task(std::coroutine_handle<promise_type> h) : handle(h) {}
    ~task() { if (handle) handle.destroy(); } // 释放协程资源
};

// 简单协程函数：模拟异步任务
task async_task() {
    std::cout << "Task start\n";
    co_await std::suspend_always{}; // 暂停，等待恢复
    std::cout << "Task resumed\n";
    co_return; // 协程结束
}

int main() {
    auto t = async_task(); // 启动协程（输出 "Task start"）
    std::cout << "Main: Coroutine suspended\n";
    t.handle.resume(); // 恢复协程（输出 "Task resumed"）
    return 0;
}
