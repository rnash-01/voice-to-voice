#pragma once

#include <data/Buffer.h>

typedef struct binTreeItem
{
	struct binTreeItem* parent;
	struct binTreeItem* lchild;
	struct binTreeItem* rchild;
	size_t				size;
	uint				index;
	BYTE*				data;
} BinTreeItem;

class BinaryTree : public Buffer
{
 public:
	BinaryTree();
	~BinaryTree() { deleteSubTree(head); }
	BYTE 	operator[]	(uint) 							override;
	BYTE* 	readBetween	(uint, uint) 					override;
	void 	appendItem	(uint, size_t, BYTE*) 			override;

	void 	clear() override;
private:
	void 	inOrderRead	(uint&, size_t&, uint&, BYTE*, BinTreeItem*);
	void	deleteSubTree(BinTreeItem*);

protected:
	BinTreeItem* head;
};
