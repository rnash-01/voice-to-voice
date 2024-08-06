#include <task/Task.h>
/**
 * "Middle" class for tasks that execute a specific function and returns a result.
 * 
 * This may seem a bit redundant - why not bind a function in 'Task.h' or in a SubTask like 'BasicTask.h'?
 * 
 * - Task.h needs to be as abstract as possible and not use templates so that it provides a general
 * interface for any sort of threading activity in one clean interface
 * 
 * - SubTasks like BasicTask.h, however, will highly likely use functions with return types - although
 * this is an abuse of inheritance, it greatly reduces code redundancy.
 * 
 * This class can be instantiated itself or inherited from to create a task that returns a result.
 */
template<typename T, typename... Args>
class FunctionTask : public Task {
public:
    FunctionTask() 
    {
        this->init();
    }
    FunctionTask(std::function<T(Args...)> const& function, Args... args)
    {
        // Store args in tuple
        this->function_ = function;
        this->args_ = std::make_tuple(args...);
        this->init();
    }
    ~FunctionTask()   = default;

    int bind(std::function<T(Args...)> const& function, Args... args)
    {
        try 
        {
            this->function_ = function;
            this->args_ = std::make_tuple(args...);
            return 0;
        }
        catch (std::exception& e) 
        {
            this->function_ = std::function<T(Args...)>();
            this->args_ = std::tuple<Args...>();
            return 1;
        }
    }

    void init()
    {
        this->run = std::function<int()>([this]() -> int {
            T result = std::apply(this->function_, this->args_);
            this->result(result);
            return 0;
        });
    }

    T       result      ()          { return this->result_; }

    
protected:
    void    result      (T r)       { this->result_ = r;    }
    
    T                               result_;
    std::tuple<Args...>             args_;
    std::function<T(Args...)>       function_;
};