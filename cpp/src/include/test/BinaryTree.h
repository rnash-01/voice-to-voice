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
		tree->first = (void*) 0;
	}

	void TearDown() override
	{
		DeleteSubTree((BinTreeItem*)tree->first);
		delete tree;
	}

	// Deleting all items in the tree
	void DeleteSubTree(BinTreeItem* item)
	{
		BinTreeItem *rchild, *lchild;

		if (!item) return;
		rchild = item->rchild;
		lchild = item->lchild;

		// Clear out data and delete the item itself
		if (item->data) delete item->data;
		delete item;

		// Now do the same on its children

		if (lchild) DeleteSubTree(lchild);
		if (rchild) DeleteSubTree(rchild);
	}

	BinaryTree_G* tree;
};
