#include <gtest/gtest.h>
#include <audio/io.h>

TEST(CreateChunkTest, DoesCreateChunk)
{
	// Test the allocation of chunk data.
	CK* chunkEven = createChunk(1, 50);
	CK* chunkOdd = createChunk(2, 51);

	// Just make sure, first of all, it creates the chunk
	// (i.e., not NULL)
	EXPECT_NE(chunkEven, (CK*) 0);

	
	// Tear down (assumes DeleteChunk works!)
	deleteChunk(chunkEven);
	deleteChunk(chunkOdd);
}

TEST(CreateChunkTest, DataIsSet)
{
	CK* chunkEven = createChunk(1, 50);
	CK* chunkOdd = createChunk(2, 51);

	ASSERT_NE(chunkEven, (CK*) 0);
	ASSERT_NE(chunkOdd, (CK*) 0);
	
	// Check the chunks' IDs and sizes
	EXPECT_EQ(chunkEven->ckID, 1);
	EXPECT_EQ(chunkEven->ckSize, 50);
	
	EXPECT_EQ(chunkOdd->ckID, 2);
	EXPECT_EQ(chunkOdd->ckSize, 51);

	// Try to compare a few values
	EXPECT_EQ(chunkEven->ckData[0], 0);
	EXPECT_EQ(chunkEven->ckData[49], 0);

	EXPECT_EQ(chunkOdd->ckData[0], 0);
	EXPECT_EQ(chunkOdd->ckData[50], 0);
	EXPECT_EQ(chunkOdd->ckData[51], 0);
}

TEST(DeleteChunkTest, DoesDeleteChunk)
{
	CK* chunk = createChunk(1, 50);
	
}
