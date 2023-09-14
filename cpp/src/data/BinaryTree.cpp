#include <data/BinaryTree.h>

BinaryTree::BinaryTree() : Buffer()
{
	head = NULL;
}

BYTE BinaryTree::operator[](uint)
{
	return 0;
}

/* inOrderRead
recursive function that reads a number of bytes from the BinaryTree
in correct order */
void BinaryTree::inOrderRead(size_t& n, BYTE* buffer, BinTreeItem* item)
{
	// NTS:
	// Function should accept 'uint start' and 'uint end', perhaps as well as a
	// 'bytesRead' parameter to help actually track what needs reading.
	// Otherwise, an actual 'readBetween' function is not possible.

	size_t originalSize = n;
	size_t offset;
	int i;
	if (item == NULL || n == 0)
		return;

	inOrderRead(n, buffer, item->lchild);

	// Now, the value of n should have changed.
	if (n == 0) return;

	offset = originalSize - n;
	for (i = 0; i < n && i < item->size; i++)
		buffer[offset + i] = item->data[i];

	n -= i;

	inOrderRead(n, buffer, item->rchild);
}

BYTE* BinaryTree::readBetween(uint start, uint end)
{

	BYTE* buffer = new BYTE[end - start + 1];
	inOrderRead(end - start + 1, buffer, this->head);
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
	item->size = n;
	item->index = i;
	item->data = buffer;

	// Now insert into the binary tree
	if (!this->head)
	{
		this->head = item;
		this->first = item;
		return;
	}

	current = (BinTreeItem*) this->head;
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

	if (item->index < ((BinTreeItem*)this->first)->index)
		this->first = item;


	return;
	
 err:
	// When something goes wrong, free up the resources.
	delete[] buffer;
	delete item;
	return;
	
}

