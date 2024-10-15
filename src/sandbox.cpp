#include <main.h>
// #include <task/BasicTask.h>
#include <task/FunctionTask.h>
#include <task/TaskPool.h>
/*
  Sandbox - for debugging/experimenting
*/

char addChar(char a, char b) {
    std::cout << "Adding two chars together captain" << std::endl;
    for (int i = 0; i < 500; i++) {
      std::cout << "(" << i << ") " << a + b;
    }
    return a + b;
}

typedef struct {
    int a;
    char b;
    float c;
    std::string d;
} TaskResult;

int main(int argc, char** argv)
{
    std::unique_ptr<TaskPool> pool = std::make_unique<TaskPool>();
    std::shared_ptr<FunctionTask<int>> task1 = std::make_unique<FunctionTask<int>>([]() -> int { return 42; });
    pool->addTask(task1);
    std::cout << pool->size() << std::endl;

    std::shared_ptr<FunctionTask<int>> task2 = std::make_unique<FunctionTask<int>>([]() -> int { return 5; });
    pool->addTask(task2);
    std::cout << pool->size() << std::endl;

    std::cout << "That's all folks" << std::endl;
}