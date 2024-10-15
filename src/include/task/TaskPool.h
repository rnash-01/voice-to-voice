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
    TaskPool() {}
    TaskPool(std::vector<std::shared_ptr<Task>> const& tasks);
    ~TaskPool() {}
    
    virtual int                     launch      ()                              override;
    virtual int                     terminate   ()                              override;
    void                            addTask     (std::shared_ptr<Task> task);
    int                             size        ()                              { return tasks_.size(); }
    std::shared_ptr<Task>           operator[]  (int i)                         { return tasks_[i]; }

protected:
    std::vector<std::shared_ptr<Task>>  tasks_;

private:
    void    scheduler();
};