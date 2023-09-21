#include <gtest/gtest.h>
#include <audio/WAVHandler.h>
#include <data/BinaryTree.h>

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
