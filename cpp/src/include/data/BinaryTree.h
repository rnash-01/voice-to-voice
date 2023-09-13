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
	BinaryTree() : Buffer() {}
	~BinaryTree() {}
	BYTE operator[](uint) override;
	BYTE* 	readBetween(uint, uint) override;
	void 	appendItem(uint, size_t, BYTE*) override;
};
