#pragma once
#include <task/FunctionTask.h>


template<typename T, typename... Args> 
class BasicTask : public FunctionTask<T, Args...> {
public:
    BasicTask() : FunctionTask<T, Args...>() {}
    BasicTask(std::function<T(Args...)> const& function, Args... args) : FunctionTask<T, Args...>(function, args...) {}
    ~BasicTask() {}
};
