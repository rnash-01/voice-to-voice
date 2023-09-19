#include <test/WAVHandler.h>

TEST_F(WAVReaderTest, DoesOpenFile)
{
	BinaryTree b;
	r->load(b);

	EXPECT_EQ(r->getNChannels(), 1);
	EXPECT_EQ(r->getSampRate(), 44100);
	EXPECT_EQ(r->getBytesPerSec(), 88200);	// 2 bytes per sample * 44100 samples per sec
	EXPECT_EQ(r->getBlockAlign(), 2);		// 16-bits per sample (16 bits * 1 channel) = 2 bytes
	EXPECT_EQ(r->getBitsPerSample(), 16);
}

TEST_F(WAVReaderTest, DoesReadData)
{
	BinaryTree b;
	r->load(b);


}
