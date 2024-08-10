#pragma once
#include <gtest/gtest.h>
#include <task/Task.h>
#include <task/FunctionTask.h>
#include <test/TaskResult.h>
#include <string>

class TaskTest : public ::testing::Test {
public:
    TaskTest() {}

protected:
    void SetUp() override {
        task = std::make_unique<FunctionTask<TaskResult>>();
    }

    void TearDown() override {}

    std::unique_ptr<FunctionTask<TaskResult>> task;
};