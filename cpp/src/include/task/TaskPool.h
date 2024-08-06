#include <task/Task.h>

class TaskPool {
public:
    TaskPool(std::vector<std::unique_ptr<Task>> const& tasks) 
    {
        this->tasks_ = tasks;
    }
    ~TaskPool();

protected:
    std::vector<std::unique_ptr<Task>> tasks_;

};