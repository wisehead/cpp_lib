#include <stdexcept>
#include "fault.h"

// Static linking function attach wrapper
class AttachStatic {
public:
    AttachStatic(const char* func_name, void* func)
        : func_name_(func_name), func_(func)
    {   
        if (attach_func_lib(const_cast<char*>(func_name_),
                            const_cast<void*>(func_))) {
            throw new std::runtime_error("Attach failed");
        }
    }

    ~AttachStatic() {
        detach_func_lib(const_cast<char*>(func_name_));
    }

    int Enable(int err, void* param = nullptr) {
        return fault_enable(func_name_, 100, err, param);
    }

    int Disable() {
        return fault_disable(func_name_);
    }

private:
    const char* func_name_;
    const void* func_;
};

// Dynamic linking function attach wrapper
class AttachShared {
public:
    AttachShared(const char* func_name, void* func)
        : func_name_(func_name), func_(func) {
        attach_func(const_cast<char*>(func_name_),
                    const_cast<void*>(func_));
    }

    ~AttachShared() {
        detach_func(const_cast<char*>(func_name_));
    }

    int Enable(int err, void* param = nullptr) {
        return fault_enable(func_name_, 100, err, param);
    }

    int Disable() {
        return fault_disable(func_name_);
    }

private:
    const char* func_name_;
    const void* func_;
};
