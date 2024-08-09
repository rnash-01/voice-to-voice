#include <task/Task.h>

/**
 * Composite pattern! Yay for design patterns!
 * TaskPool is the composite class that inherits the 'Component' Task, and contains a list of 'Leaf' SubTasks.
 * 
 * Chosen to allow TaskPools to be included in a list of tasks.
 * (Bit overkill, but this project is helping me learn cool C++ stuff)
 */
class TaskPool : public Task {
public:
    TaskPool(std::vector<std::shared_ptr<Task>> const& tasks) 
    {
        this->tasks_ = tasks;
        this->run = std::function<int()>([this]() -> int {
            try 
            {
                this->scheduler();
                this->success();
                return 0;
            }
            catch (std::exception& e) 
            {
                this->failure();
                return 1;
            }
        });
    }
    ~TaskPool();


protected:
    std::vector<std::shared_ptr<Task>> tasks_;

private:
    void scheduler() 
    {
        for (auto task : this->tasks_) 
        {
            task->launch();
        }
    }

};