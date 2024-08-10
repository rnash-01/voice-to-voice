#include <test/TaskPool.h>


TEST_F(TaskPoolTest, AddTask)
{   
    ASSERT_EQ(pool->size(), 0);
    // FunctionTask<TaskResult, int, char, float, std::string> 
    // task([this](int a, char b, float c, std::string d) -> TaskResult { 
    //     return { a, b, c, d }; 
    // }, 42, 'a', 3.14, "HELLO");

    std::shared_ptr<FunctionTask<int>> 
    task1 = std::make_shared<FunctionTask<int>>([]() -> int { return 42; });
    pool->addTask(task1);
    EXPECT_EQ(pool->size(), 1);

    std::shared_ptr<FunctionTask<int>> 
    task2 = std::make_shared<FunctionTask<int>>([]() -> int { return 5; });
    pool->addTask(task2);
    EXPECT_EQ(pool->size(), 2);
}

TEST_F(TaskPoolTest, DoesRunTests)
{
    ASSERT_EQ(pool->size(), 0);

    std::shared_ptr<FunctionTask<TaskResult, int, char, float, std::string>>
    task1 = std::make_shared<FunctionTask<TaskResult, int, char, float, std::string>>(
        [this](int a, char b, float c, std::string d) -> TaskResult { 
                return { a, b, c, d }; 
        }, 42, 'a', 3.14, "HELLO"
    );

    std::shared_ptr<FunctionTask<int>>
    task2 = std::make_shared<FunctionTask<int>>([]() -> int { return 5; });

    pool->addTask(task1);
    pool->addTask(task2);

    ASSERT_EQ(pool->size(), 2);
    pool->launch();
    pool->terminate();

    EXPECT_EQ(pool->status(), pool->status() & S_RESET);

    EXPECT_EQ(task1->result().a, 42);
    EXPECT_EQ(task1->result().b, 'a');
    EXPECT_EQ(task1->result().c, 3.14f);
    EXPECT_EQ(task1->result().d, "HELLO");
    EXPECT_EQ(task2->result(), 5);
}