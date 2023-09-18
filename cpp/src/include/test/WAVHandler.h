#include <gtest/gtest.h>
#include <audio/WAVHandler.h>

class WAVReaderTest : public ::testing::Test
{
protected:
	WAVReader* r;

	void SetUp() override
	{
		r = new WAVReader(0, "./test.wav");
	}

	void TearDown() override
	{
		delete r;
	}
};
