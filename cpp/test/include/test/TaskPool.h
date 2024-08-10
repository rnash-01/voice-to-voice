#pragma once
#include <gtest/gtest.h>
#include <task/TaskPool.h>
#include <task/FunctionTask.h>
#include <test/TaskResult.h>
#include <string>


class TaskPoolTest : public ::testing::Test {
public:
    TaskPoolTest() {}

protected:
    void SetUp() override {
        pool = std::make_unique<TaskPool>();
    }

    void TearDown() override {}

    std::unique_ptr<TaskPool> pool;
};