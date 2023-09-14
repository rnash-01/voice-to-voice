#pragma once

#include <gtest/gtest.h>
#include <data/BinaryTree.h>

class BinaryTree_G : public BinaryTree
{
public:

	friend class BinaryTreeTest;

	FRIEND_TEST(BinaryTreeTest, DoesAppendItem);
	FRIEND_TEST(BinaryTreeTest, DoesNotAppendNULL);
	FRIEND_TEST(BinaryTreeTest, DoesAppendManyItems);


};

class BinaryTreeTest : public ::testing::Test{
public:
	BinaryTreeTest() {}
protected:
	void SetUp() override
	{
		tree = new BinaryTree_G();
		tree->first = NULL;
		tree->head = NULL;
	}

	void TearDown() override
	{
		delete tree;
	}

	// Deleting all items in the tree

	BinaryTree_G* tree;
};

class BinaryTreeTestPopulated : public ::testing::Test {
public:
	BinaryTreeTestPopulated() {}

protected:
	void SetUp() override {
		tree = new BinaryTree_G();
		BYTE* buffers[5];
		size_t sizes[] = { 256, 256, 256, 128, 64 };
		for (int i = 0; i < 5; i++)
		{
			buffers[i] = new BYTE[sizes[i]];
			for (int j = 0; j < sizes[i]; j++) buffers[i][j] = i + 1;
		}

		tree->appendItem(3, 256, buffers[2]);
		tree->appendItem(1, 256, buffers[0]);
		tree->appendItem(2, 256, buffers[1]);
		tree->appendItem(5, 64, buffers[4]);
		tree->appendItem(4, 128, buffers[3]);
	}
	void TearDown() override {
		delete tree;
		delete buffer;
	}
	BinaryTree_G* tree;
	BYTE* buffer;
};
