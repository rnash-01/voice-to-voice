#pragma once

#include <gtest/gtest.h>
#include <audio/WAVHandler.h>
#include <data/BinaryTree.h>
#include <cmath>

class WAVReaderTest : public ::testing::Test
{
protected:
	WAVReader* r;

	void SetUp() override
	{
		r = new WAVReader("./test.wav");
		r->setSamplesPerBufItem(10);
	}

	void TearDown() override
	{
		delete r;
	}
};

class WAVWriterTest : public ::testing::Test
{
protected:
	WAVWriter* w;
	BinaryTree sine;


	void SetUp() override
	{
		w = new WAVWriter("./test_out.wav");
	}

	void TearDown() override
	{
		delete w;
	}
	
};
