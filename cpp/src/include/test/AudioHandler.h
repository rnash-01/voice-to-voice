#pragma once

#include <gtest/gtest.h>
#include <audio/AudioHandler.h>
#include <data/BinaryTree.h>

// Define dummy callback
int dummyCallback(BYTE* buffer, size_t n)
{
	std::cout << "this is a dummy callback function called after the buffer is full" << std::endl;
	for (int i = 0; i < n; i++)
		std::cout << buffer[i];
	std::cout << std::endl;
	return 0;
}

class AudioReader_G : public AudioReader
{
	friend class AudioReaderTest;
	FRIEND_TEST(AudioReaderTest, StartLoadDoesCreateControlThread);
	FRIEND_TEST(AudioReaderTest, DoesBindCallBack);
	FRIEND_TEST(AudioReaderTest, DoesRunCallbackFromThread);
public:
	AudioReader_G(size_t s) : AudioReader(s) {}

private:
	void load(Buffer&) override {
		BYTE* dummyBuffer = new BYTE[256];
		if (this->onLoad)
			this->onLoad(dummyBuffer, 256);
		
		delete[] dummyBuffer;
	}

};


class AudioReaderTest : public ::testing::Test
{
protected:
	void SetUp() override {
		a = new AudioReader_G(256);
	}

	void TearDown() override {
		delete a;
	}

	AudioReader_G* a;
};
