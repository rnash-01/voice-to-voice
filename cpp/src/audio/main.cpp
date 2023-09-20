#include "main.h"
using namepsace std;
int main(int argc, char** argv)
{
	printf("HI\n");
	cout << "HELLO" << endl;	
	AudioReader* a = new AudioReader(5);
	cout << "Size is: " << a.getSize() << endl;
	return 0;
}
