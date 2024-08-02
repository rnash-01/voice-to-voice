#include <gtest/gtest.h>
#include <task/Task.h>
#include <string>

typedef struct taskresult {
    int a;
    char b;
    float c;
    std::string d;
} TaskResult;

class BasicTask : public Task<TaskResult> {
public:
    BasicTask() {
      this->init();
    }

    BasicTask(std::function<TaskResult()> const& function) : Task(function) {
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

class TaskTest : public ::testing::Test {
public:
    TaskTest() {}

protected:
    void SetUp() override {
        task = std::make_unique<BasicTask>();
    }

    void TearDown() override {}

    std::unique_ptr<BasicTask> task;
};