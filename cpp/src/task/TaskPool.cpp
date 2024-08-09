#include <task/TaskPool.h>

TaskPool::TaskPool (std::vector<std::shared_ptr<Task>> const& tasks) 
{
    this->tasks_ = tasks;
    this->run = std::function<int()>([this]() -> int {
        // try 
        // {
        //     this->scheduler();
        //     this->success();
        //     return 0;
        // }
        // catch (std::exception& e) 
        // {
        //     this->failure();
        //     return 1;
        // }
        return 0;
    });
}

int TaskPool::launch () 
{
    this->status((this->status() & S_RESET) | S_RUNNING);
    for (auto task : this->tasks_) 
    {
        task->launch();
    }
    return 0;
}

int TaskPool::terminate ()
{
    for (auto task : this->tasks_) 
    {
        task->terminate();
    }
    return 0;
}

void TaskPool::scheduler ()
{
    // Lol I just do nothing.
}