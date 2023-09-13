#include <data/BinaryTree.h>

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
	char lr;								// Whether 'current' is the left/right child of previous node.
	
	// Do not copy from a NULL buffer
	if (!old) return;
	
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
		prev = current;
		if (item->index < current->index)
		{
			current = current->lchild;
			lr = 0;
		}
		else if (item->index > current->index)
		{
			current = current->rchild;
			lr = 1;
		}
		else goto err;		// Two equal indices can't exist in the list.
	}

	// Now that we've reached the end of the path in the tree, set the pointers
	// to add the item.

	// prev + 1 points to the lchild proprety of binTreeItem.
	// if lr = 0, then this is fine. If lr = 1, then we are pointing
	// to rchild, as desired.

	item->parent = prev;
	*((BinTreeItem**)prev + 1 + lr) = item; // DEBUG: keep an eye on this one.


	return;
	
 err:
	// When something goes wrong, free up the resources.
	delete[] buffer;
	delete item;
	return;
	
}

