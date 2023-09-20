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
	BYTE fileBuf[16];

	BYTE* bBuf;
	std::ifstream* is;

	// First, choose '5' as the number of samples per binary tree item.
	r->setSamplesPerBufItem(5);
	r->load(b);
	EXPECT_EQ(b.getSize(), r->getFSize());

	// Now try with non-divisible number.
	b.clear();
	ASSERT_EQ(b.getSize(), 0);

	r->setSamplesPerBufItem(11);
	r->load(b);
	EXPECT_NE(b.getSize(), 0);
	EXPECT_EQ(b.getSize(), r->getFSize());

	// Try with a bigger number, just in case.
	b.clear();
	ASSERT_EQ(b.getSize(), 0);

	r->setSamplesPerBufItem(26723);
	r->load(b);
	EXPECT_NE(b.getSize(), 0);
	EXPECT_EQ(b.getSize(), r->getFSize());

	// Check that chunks of the WAV file match
	// that of the Binary Tree.
	b.clear();
	ASSERT_EQ(b.getSize(), 0);

	r->setSamplesPerBufItem(8);
	r->load(b);
	ASSERT_NE(b.getSize(), 0);

	is = new std::ifstream("./test.wav", std::ifstream::binary);
	is->seekg(44);	// skip over info and format chunk, which contains 36
	// Bits per sample = 16 (2 * 8)
	
	for (int i = 0; i < r->getFSize(); i += 16)
	{
		is->read((char*)fileBuf, 16);
		bBuf = b.readBetween(i, i + is->gcount() - 1);
		
		for (int j = 0; j < is->gcount(); j++)
			ASSERT_EQ(bBuf[j], fileBuf[j]);

		delete[] bBuf;
	}
	is->close();
}
