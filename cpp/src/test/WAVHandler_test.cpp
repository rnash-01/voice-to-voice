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

TEST_F(WAVReaderTest, BadInput)
{
	BinaryTree b;
	EXPECT_NO_THROW({
			r->setSamplesPerBufItem(0);
			r->load(b);
		});
}


// %%%%%%% WAVWriter %%%%%%%%
TEST_F(WAVWriterTest, DoesOpenFile)
{
	EXPECT_EQ(w->getNChannels(), 1);
	EXPECT_EQ(w->getSampRate(), 44100);
	EXPECT_EQ(w->getBytesPerSec(), 88200);
	EXPECT_EQ(w->getBlockAlign(), 2);
 	EXPECT_EQ(w->getBitsPerSample(), 16);


	BinaryTree b;
	w->load(b);
}

TEST_F(WAVWriterTest, DoesSetNChannels)
{
	int16_t blockAlign;
	int32_t bytesPerSec;
	EXPECT_EQ(w->getNChannels(), 1);

	blockAlign = w->getBlockAlign();
	bytesPerSec = w->getBytesPerSec();
	
	w->setNChannels(2);
	EXPECT_EQ(w->getNChannels(), 2);
	EXPECT_EQ(w->getBlockAlign(), 2 * blockAlign);
	EXPECT_EQ(w->getBytesPerSec(), 2 * bytesPerSec);
}

TEST_F(WAVWriterTest, DoesSetSampRate)
{
	int16_t blockAlign;
	int32_t bytesPerSec;
	
	EXPECT_EQ(w->getSampRate(), 44100);

	blockAlign = w->getBlockAlign();
	bytesPerSec = w->getBytesPerSec();
	
	w->setSampRate(22050);
	EXPECT_EQ(w->getSampRate(), 22050);
	EXPECT_EQ(w->getBlockAlign(), blockAlign);
	EXPECT_EQ(w->getBytesPerSec(), bytesPerSec / 2);
}

TEST_F(WAVWriterTest, DoesSetBitsPerSamp)
{
	int16_t blockAlign;
	int32_t bytesPerSec;
	
	EXPECT_EQ(w->getBitsPerSample(), 16);

	blockAlign = w->getBlockAlign();
	bytesPerSec = w->getBytesPerSec();
	
	w->setBitsPerSample(32);
	EXPECT_EQ(w->getBitsPerSample(), 32);
	EXPECT_EQ(w->getBlockAlign(), 2 * blockAlign);
	EXPECT_EQ(w->getBytesPerSec(), 2 * bytesPerSec);
}

TEST_F(WAVWriterTest, DoesWriteSine)
{
	Buffer *b = new BinaryTree;
	size_t bufSize = 441 * w->getBlockAlign();
	BYTE *buf = new BYTE[bufSize];

	// In this case, two bytes per sample.
	int16_t sineVal;
	std::cout << bufSize << std::endl;
	for (int i = 0; i < 44100; i++)		
	{

		sineVal = (int16_t)(sin((double)i/44100 * 2.0 * M_PI * 1000.0) * 30000);

		for (int j = 0; j < w->getNChannels(); j++)
		{
			*((int16_t*)&buf[(i * w->getBlockAlign() + (j * w->getBitsPerSample()/8)) % bufSize]) = sineVal;
		}

		if (i % 441 == 440)
			b->appendItem(i/441, bufSize, buf);


	}

	ASSERT_EQ((*b)[0], 0);
	for (int i = 0; i < 100; i++) std::cout << ((int16_t*)b->readBetween(i*2, (i * 2) + 2))[0] << std::endl;

	w->load(*b);
	delete buf;
}


