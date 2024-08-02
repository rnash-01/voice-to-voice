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
    
    result = task->result();

    EXPECT_EQ(result.a, 42);
    EXPECT_EQ(result.b, 3);
    EXPECT_EQ(result.c, (float)3.14);
    EXPECT_STREQ(result.d.c_str(), "HELLO");
}