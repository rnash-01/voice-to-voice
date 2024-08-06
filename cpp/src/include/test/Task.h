#pragma once
#include <gtest/gtest.h>
#include <task/Task.h>
#include <task/BasicTask.h>
#include <string>

typedef struct taskresult {
    int a;
    char b;
    float c;
    std::string d;
} TaskResult;

class TaskTest : public ::testing::Test {
public:
    TaskTest() {}

protected:
    void SetUp() override {
        task = std::make_unique<BasicTask<TaskResult>>();
    }

    void TearDown() override {}

    std::unique_ptr<BasicTask<TaskResult>> task;
};