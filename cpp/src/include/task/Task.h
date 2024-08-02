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

#include <thread>
#include <memory>
#include <functional>
template <typename T, typename... Args> class Task {
public:
  // Constructors & Destructor
  Task    () 
  {
    this->result_ = T();
    this->status_ = 0;
  }

  Task    (std::function<T(Args...)> const& function) : Task()
  {
    this->bind(function);
  }

  ~Task   () {}

  // Thread management & function binding/execution
  int launch ()  
  {
    taskThread = std::thread(this->run);
    return 0;
  }

  int terminate ()
  {
    taskThread.join();
    return 0;
  }

  int bind (std::function<T(Args...)> const& function) 
  {
    this->function_ = function;
    return 0;
  }

  int execute ()
  {
    this->result(this->function_());
    return 0;
  }

  // To be implemented by child classes
  virtual void          init      () = 0;
  std::function<int()>  run;

  // Setters & Getters
  T                 result    ()                { return this->result_; }
  int               status    ()                { return this->status_; }
  std::thread::id   threadId  ()                { return taskThread.get_id(); }

protected:
  std::function<T(Args...)>       function_;
  int                             status_;
  T                               result_;

  // Setters & Getters
  void              result    (T const& val)    { this->result_ = val; }
  void              status    (int const& val)  { this->status_ = val; }
  
    
private:
  std::thread     taskThread;
};