#include <task/Task.h>

Task::Task()
{
  this->status_ = 0;
  this->status_lock_ = false;
}

/**
 * @brief Creates thread to run the task. (DEFAULT IMPLEMENTATION)
 */
int Task::launch ()  
{
    this->status((this->status() & S_RESET) | S_RUNNING);
    taskThread = std::thread([this]() -> void {
        try 
        {
            this->run();
            this->success();
        }
        catch (std::exception& e) 
        {
            this->failure();
        }
    });
    return 0;
}

/**
 * @brief Checks if the task is running
 */
int Task::check ()
{
    if (this->status() & 2) return 1;
    return 0;
}

/**
 * @brief (Blocking) Terminates the task thread (DEFAULT IMPLEMENTATION)
 */
int Task::terminate ()
{
    while (this->status() & S_RESET != this->status() && !taskThread.joinable());
    taskThread.join();
    return 0;
}

/**
 * @brief Set the last two bits of status to 00 (idle/success)
 */
void Task::success ()
{
    // Set status_lock_ to true
    while (status_lock_);
    status_lock_ = true;
    this->status(this->status() & S_RESET);
    status_lock_ = false;
}

/**
 * @brief Set the last two bits of status to 01 (failure)
 */
void Task::failure ()
{
    while(status_lock_);
    status_lock_ = true;
    this->status((this->status() & S_RESET) | S_FAILURE);
    status_lock_ = false;
}