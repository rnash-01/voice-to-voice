#include <main.h>
#include <task/Task.h>

class BasicTask : public Task<int> {
public:
    BasicTask() {
      this->init();
    }

    BasicTask(std::function<int()> const& function) : Task(function) {
      this->init();
    }
    ~BasicTask() {}

    void init() override {
      this->run = std::function<int()>([this]() -> int { 
        this->execute();
        return 0; 
      });
    }

};
/*
  Sandbox - for debugging/experimenting
*/
int main(int argc, char** argv)
{
    BasicTask task;
    std::cout << "Launching Thread" << std::endl;
    task.bind([]() -> int { 
      return 5; 
    });
    task.launch();
    std::cout << "Result (main thread): " << task.result() << std::endl;
    task.terminate();
    std::cout << "Thread terminated: " << task.result() << std::endl;
    return 0;
}