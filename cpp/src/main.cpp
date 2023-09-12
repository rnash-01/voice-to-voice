#include <main.h>

int main(int argc, char** argv)
{
	AudioReader* a = new AudioReader(15);
	std::cout << "Size is: " << a->getSize() << std::endl;
	delete a;
	std::cout << "Deleted successfully" << std::endl;
	return 0;
}
