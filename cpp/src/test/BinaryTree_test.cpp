#include <test/BinaryTree.h>

TEST_F(BinaryTreeTest, DoesAppendItem)
{
	BYTE* buffer = new BYTE[256];
	int i = 0;

	for (i; i < 256;) buffer[i++] = i;

	ASSERT_EQ(tree->first, (void*) 0);
	ASSERT_EQ(tree->head, (BinTreeItem*) 0);

	tree->appendItem(1, 256, buffer);
	EXPECT_NE(tree->first, (void*) 0);
	EXPECT_NE(tree->head, (BinTreeItem*) 0);
	for (i = 0; i < 256; i++)
		EXPECT_EQ(((BinTreeItem*)tree->head)->data[i], i);
}

TEST_F(BinaryTreeTest, DoesNotAppendNULL)
{
	BYTE* nullBuffer = (BYTE*) 0;
	BYTE* realBuffer = new BYTE[256];
	int i = 0;

	for (i; i < 256;) realBuffer[i++] = i;

	ASSERT_EQ(tree->head, (void*) 0);

	tree->appendItem(1, 256, realBuffer);
	tree->appendItem(2, 256, nullBuffer);

	// We expect that no item has actually been added.
	EXPECT_EQ(tree->head->rchild, (BinTreeItem*) 0);
}

TEST_F(BinaryTreeTest, DoesAppendManyItems)
{
	BYTE* buffers[5];
	uint i = 0, j = 0;
	BinTreeItem* current;

	ASSERT_EQ(tree->first, (void*) 0);

	for (i; i < 5; i++)
	{
		buffers[i] = new BYTE[256];
		for (j = 0; j < 256;) buffers[i][j++] = j;
		tree->appendItem(i + 1, 256, buffers[i]);
	}


	// Tree will be unbalanced. So, we expect 1 to be the parent,
	// 2 to be its rchild, 3 to be 2's rchild, etc.
	current = (BinTreeItem*) tree->head;
	
	for (i = 0; i < 5; i++)
	{
		ASSERT_NE(current, (BinTreeItem*)0);
		current = current->rchild;
	}
	EXPECT_EQ(current, (BinTreeItem*)0);
	EXPECT_EQ(((BinTreeItem*)tree->first)->index, 1);
}

TEST_F(BinaryTreeTestPopulated, DoesReadOneItem)
{
	// This test expects the 'first' item in the tree (with index 1),
	// which is 256 bytes long, to be copied over into the buffer.
	// It's been set up so that we should expect all 1's in the buffer.
	buffer = tree->readBetween(0, 255);
	for (int i = 0; i < 256; i++) ASSERT_EQ(buffer[i], 1);
}

TEST_F(BinaryTreeTestPopulated, DoesReadAllItems)
{
	// Like the previous test, but we try to read the entire
	// contents of the buffers of the tree, in order.
	// Total buffer size should be 960 bytes.
	buffer = tree->readBetween(0, 959);

	// First three segments are 256 bytes long.
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 256; j++)
			ASSERT_EQ(buffer[i*256 + j], i + 1);

	// Fourth is 128 bytes
	for (int j = 0; j < 128; j++)
		ASSERT_EQ(buffer[768 + j], 4);

	// Finally, fifth is 64 bytes
	for (int j = 0; j < 64; j++)
		ASSERT_EQ(buffer[896 + j], 5);

}

TEST_F(BinaryTreeTestPopulated, DoesReadStartToFin)
{
	// First test starts at 10, ends at 255
	buffer = tree->readBetween(10, 255);
	for (int i = 0; i < 246; i++) ASSERT_EQ(buffer[i], 1);

	delete[] buffer;

	// Second test starts at 256, ends at 300
	buffer = tree->readBetween(256, 300);
	for (int i = 0; i < 45; i++)
		ASSERT_EQ(buffer[i], 2);

	delete[] buffer;

	// Third test starts at 293, ends at 852
	buffer = tree->readBetween(293, 852);
	for (int i = 293; i < 512; i++) ASSERT_EQ(buffer[i - 293], 2);
	for (int i = 512; i < 768; i++)	ASSERT_EQ(buffer[i - 293], 3);
	for (int i = 768; i < 852; i++) ASSERT_EQ(buffer[i - 293], 4);

}

TEST_F(BinaryTreeTestPopulated, AccessOpDoesRead)
{
	// Try reading edge cases.
	EXPECT_EQ((*tree)[0], 1);
	EXPECT_EQ((*tree)[255], 1);
	EXPECT_EQ((*tree)[256], 2);
	EXPECT_EQ((*tree)[511], 2);
	EXPECT_EQ((*tree)[512], 3);
	EXPECT_EQ((*tree)[767], 3);
	EXPECT_EQ((*tree)[768], 4);

}
