#include <data/BinaryTree.h>

BinaryTree::BinaryTree() : Buffer()
{

}

BYTE BinaryTree::operator[](uint)
{
	return 0;
}


BYTE* BinaryTree::readBetween(uint start, uint end)
{
	return (BYTE*) 0;
}

void BinaryTree::appendItem(uint i, size_t n, BYTE* old)
{
	BinTreeItem *item, *current, *prev;
	BYTE* buffer;

	buffer = new BYTE[n];
	item = new BinTreeItem;
	
	if (!memcpy(buffer, old, n))
	{
		std::cerr << "Could not copy memory between buffers" << std::endl;
		goto err;
	}

	item->parent = item->lchild = item->rchild = (BinTreeItem*) 0;
	item->index = i;
	item->data = buffer;

	// Now insert into the binary tree
	if (!this->first)
	{
		this->first = item;
		return;
	}

	current = (BinTreeItem*) this->first;
	while (current)
	{
		if (item->index < current->index)
			current = current->lchild;
		else if (item->index > current->index)
			current = current->rchild;
		else goto err;		// Two equal indices can't exist in the list.
	}
	
 err:
	// When something goes wrong, free up the resources.
	delete buffer;
	delete item;
	return;
	
}

