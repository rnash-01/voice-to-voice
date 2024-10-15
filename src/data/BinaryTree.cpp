#include <data/BinaryTree.h>

BinaryTree::BinaryTree() : Buffer()
{
	head = nullptr;
}

void BinaryTree::deleteSubTree(BinTreeItem* item)
{
	BinTreeItem *rchild, *lchild;

	if (!item) return;
	rchild = item->rchild;
	lchild = item->lchild;

	// Clear out data and delete the item itself
	if (item->data) delete[] item->data;
	delete item;

	// Now do the same on its children

	if (lchild) deleteSubTree(lchild);
	if (rchild) deleteSubTree(rchild);
}

void BinaryTree::clear()
{
	if (!this->head) return;
	deleteSubTree(this->head);
	this->head = nullptr;
	this->size = 0;
}

BYTE BinaryTree::operator[](uint index)
{
	// We already have 'readBetween', and accessing
	// data from the BinaryTree is principally the same
	// here. So, just use it for a single value.
	BYTE value;
	BYTE* temp;
	temp = readBetween(index, index);
	value = temp[0];

	return value;
}

/* inOrderRead
recursive function that reads a number of bytes from the BinaryTree
in correct order */
void BinaryTree::inOrderRead(uint &start, size_t& n, uint& offset, BYTE* buffer, BinTreeItem* item)
{
	size_t originalSize = n;
	int i = 0;
	
	if (item == nullptr || n == 0)
		return;

	inOrderRead(start, n, offset, buffer, item->lchild);

	// Now, the value of n should have changed.
	if (n == 0) return;

	for (i = 0; i < n && i + start < item->size; i++)
		buffer[offset + i] = item->data[start + i];

	// Either start is not contained in the current item's buffer,
	// so we take this buffer's size off the start and inspect the next one
	// OR the start IS contained in the current item's buffer, in which case,
	// we need no offset for the next buffer.
	if (item->size < start) start -= item->size;
	else start = 0;	
	n -= i;
	offset += i;

	inOrderRead(start, n, offset, buffer, item->rchild);
}

BYTE* BinaryTree::readBetween(uint start, uint end)
{

	BYTE* buffer = new BYTE[end - start + 1];
	size_t n = end - start + 1;
	uint s = start;
	uint offset = 0;
	inOrderRead(s, n, offset, buffer, this->head);

	return buffer;
}

void BinaryTree::appendItem(uint i, size_t n, BYTE* old)
{
	BinTreeItem *item, *current, *prev;
	BYTE* buffer;
	char lr;								// Whether 'current' is the left/right child of previous node.
	
	// Do not copy from a nullptr buffer
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
		this->size += item->size;
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

	this->size += item->size;
	return;
	
 err:
	// When something goes wrong, free up the resources.
	delete[] buffer;
	delete item;
	return;
}

