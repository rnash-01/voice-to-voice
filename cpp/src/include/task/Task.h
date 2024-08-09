/**
 * Abstract base class for task runners (interface with some initialisation)
 * 
 * For each Task instance, a thread is created rather than a process. The rationale is that there only needs to be one main 'control' process.
    - Having different processes for each task would make passing control information between the task process and the main process marginally trickier.
    - Furthermore, from an architectural perspective, it would undermine the goal of Task in allowing its child classes to decide how to split
  the load up
    - Therefore, the publicly exposed parts of any instance of Task or its children comprise mechanisms for exchanging control information between the main
  thread and the task thread. Internally, children like ProcessTask or GPUTask (potentially) may spawn a separate process or
  send instructions and data to the GPU. 
    - Using concurrency in the first place for this is to allow past audio data to be processed while current audio data is collected.
    - There may be better ways but this is what I've come up with! :)
*/
#pragma once
#include <thread>
#include <memory>
#include <functional>
#include <iostream>
#include <atomic>

/* 
Flags:
Status value currently looks like this bit string - each unique letter represents which segment a bit belongs to.
Bit string: ss
  s - current success/failure/run status of the task.

Right now it looks a bit convoluted, but I'm allowing some leeway for additional flags in future.
If in future it turns out that no additional flags are needed, then the status value will be simplified.
*/
#define S_RESET -4 // i.e., 1111...111100
#define S_IDLE_SUCCESS 0
#define S_FAILURE 1
#define S_RUNNING 2
#define S_WAITING 3

/**
 * Some context for how this is supposed to work from an architectural perspective:
 * The 'Task' class is supposed to handle the control thread for the ask. It contains code which will be needed
 * by all derived classes. The derived classes will contain the actual code to be executed by the task.
 * 
 * Some methods appear identical in purpose. They are, more or less, but differentiated by whether they are the responsibility
 * of this main Task class or of the child (SubTask) classes. Note that SubTask is not an actual class implemented in this codebase, 
 * but represents any child class
 * 
 * I expect code to be executed in the following order:
 * 
 * Set up:
 * - Task constructor
 * - SubTask constructor
 * - SubTask::init
 * - Task::bind (if not already bound in SubTask constructor)
 * 
 * Execution:
 * - Task::launch -> to spawn the thread. 
 * - SubTask::run -> final preparations to the environment in which 'execute' is run, followed by 'execute' 
 *      (note that SubTask::run is technically an attribute of type std::function<int()> and not a method. But it's basically a method. Right? Right.)
 * - Task::execute -> run the bound function and store the result or handle exceptions. 
 * 
 * Tear down:
 * - Task::terminate -> Waits for thread to finish.
 * - SubTask destructor
 * - Task destructor
 * 
 * Other notes:
 * - Parameters are defined as attributes in the defined SubTask. It would be ideal if 
 *   Task::launch could be called with the parameters to save the need. However, in order to allow for
 *   pools of tasks, launch must accept no arguments - or else, 
 */

class Task {
public:
  // Constructors & Destructor
  Task    () 
  {
    this->status_ = 0;
    this->status_lock_ = false;
  }
  ~Task   () {}

  // Thread management & function binding/execution
  int launch ()  
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
  int check ()
  {
    if (this->status() & 2) return 1;
    return 0;
  }

  /**
   * @brief (Blocking) Terminates the task thread
   */
  int terminate ()
  {
    while (!taskThread.joinable());
    taskThread.join();
    return 0;
  }

  void success ()
  {
    // Set status_lock_ to true
    while (status_lock_);
    status_lock_ = true;
    this->status(this->status() & S_RESET);
    status_lock_ = false;
  }

  void failure ()
  {
    while(status_lock_);
    status_lock_ = true;
    this->status((this->status() & S_RESET) | S_FAILURE);
    status_lock_ = false;
  }

  // To be implemented by child classes
  std::function<int()>  run;

  // Setters & Getters
  int               status    ()                { return this->status_; }
  std::thread::id   threadId  ()                { return taskThread.get_id(); }

protected:
  int                             status_;
  std::atomic<bool>               status_lock_;

  void              status    (int const& val)  { this->status_ = val;  }

    
private:
  std::thread       taskThread;
};