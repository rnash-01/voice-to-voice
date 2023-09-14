
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
