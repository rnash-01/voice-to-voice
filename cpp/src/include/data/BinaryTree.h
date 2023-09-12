#pragma once

#include <data/Buffer.h>

typedef struct binTreeItem
{
	struct binTreeItem* parent;
	struct binTreeItem* lchild;
	struct binTreeItem* rchild;
	uint				index;
	BYTE*				data;
} BinTreeItem;

class BinaryTree : public Buffer
{
 public:
	BinaryTree();
	~BinaryTree() {}
	BYTE operator[](uint);
	BYTE* 	readBetween(uint, uint);
	void 	appendItem(uint, size_t, BYTE*);
};
