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
int main(int argc, char** argv)
{
    // Instantiate tasks
    std::shared_ptr<FunctionTask<int, std::string>> 
    task1 = std::make_shared<FunctionTask<int, std::string>>(([](std::string str) -> int {
        std::cout << "Task output: " << str << std::endl;
        return 0;
    }), "HI!");
    
    std::shared_ptr<FunctionTask<int, int, int>> 
    task2 = std::make_shared<FunctionTask<int, int, int>>([](int a, int b) -> int {
        for (int i = 0; i < 500; i++) {
            std::cout << std::endl;
        }
        return a + b;
    }, 590, 500);
    
    std::shared_ptr<FunctionTask<char, char, char>> 
    task3 = std::make_shared<FunctionTask<char, char, char>>(addChar, 65, 1);

    // Create TaskPool
    std::vector<std::shared_ptr<Task>> tasks = std::vector<std::shared_ptr<Task>>();
    tasks.insert(tasks.end(), task1);
    tasks.insert(tasks.end(), task2);
    tasks.insert(tasks.end(), task3);

    TaskPool pool(tasks);
    pool.launch();
    pool.terminate();
    // tasks.insert(tasks.end(), std::make_unique<FunctionTask<int, std::string>>());
    // tasks.insert(tasks.end(), std::make_unique<FunctionTask<int, int, int>>(task2));
    // tasks.insert(tasks.end(), std::make_unique<FunctionTask<char, char, char>>(task3));
}