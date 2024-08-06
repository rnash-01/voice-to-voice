#include <test/Task.h>
TEST_F(TaskTest, DoesCompleteTask)
{
    TaskResult result = task->result();
    EXPECT_NE(result.a, 42);
    EXPECT_NE(result.b, 3);
    EXPECT_NE(result.c, (float)3.14);
    EXPECT_STRNE(result.d.c_str(), "HELLO");

    task->bind([]() -> TaskResult { return {
        42,
        3,
        3.14,
        "HELLO"
    }; });

	task->launch();
    EXPECT_NE(std::this_thread::get_id(), task->threadId());
    task->terminate();
    EXPECT_EQ(task->status() & 1, S_IDLE_SUCCESS);
    
    result = task->result();

    EXPECT_EQ(result.a, 42);
    EXPECT_EQ(result.b, 3);
    EXPECT_EQ(result.c, (float)3.14);
    EXPECT_STREQ(result.d.c_str(), "HELLO");
}

/**
 * Tests that the *main* thread doesn't die if the *task* thread dies.
 */
TEST_F(TaskTest, HandlesErrorGracefully) 
{
    task->bind([]() -> TaskResult {
        throw std::runtime_error("An error occurred");
        return {
            42,
            3,
            3.14,
            "HELLO"
        };
    });

    task->launch();
    task->terminate();
    
    TaskResult result = task->result();

    EXPECT_EQ(task->status() & S_FAILURE, S_FAILURE);

    // We know the thread will fail - so we shouldn't expect the result to be the same as the one returned by the bound function.
    EXPECT_EQ(result.a, 0);
    EXPECT_EQ(result.b, 0);
    EXPECT_EQ(result.c, 0);
    EXPECT_STREQ(result.d.c_str(), "");
}
