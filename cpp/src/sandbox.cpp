#include <main.h>
#include <task/BasicTask.h>
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
    std::unique_ptr<FunctionTask<int, std::string>> task1 = std::make_unique<FunctionTask<int, std::string>>();
    task1->bind([](std::string str) -> int {
        std::cout << "Task output: " << str << std::endl;
        return 0;
    }, "HI");
    // FunctionTask<int, int, int> task2([](int a, int b) -> int {
    //     for (int i = 0; i < 500; i++) {
    //         std::cout << std::endl;
    //     }
    //     return a + b;
    // }, 590, 500);
    // FunctionTask<char, char, char> task3(addChar, 65, 1);

    // Create TaskPool
    std::vector<std::unique_ptr<Task>> tasks;
    tasks.insert(tasks.end(), std::make_unique<FunctionTask<int, std::string>>());
    // tasks.insert(tasks.end(), std::make_unique<FunctionTask<int, int, int>>(task2));
    // tasks.insert(tasks.end(), std::make_unique<FunctionTask<char, char, char>>(task3));

    

    
}