#include <main.h>

int main(int argc, char** argv)
{
	BinaryTree* B = new BinaryTree();

	for (int i = 0; i < 5; i++)
	{
		BYTE* buffer = new BYTE[256];
		B->appendItem(i + 1, 256, buffer);
	}
}
