#include <main.h>

/*
  Sandbox - for debugging/experimenting
*/
int main(int argc, char** argv)
{
	WAVReader r(0, "./test.wav");
	r.load();

	std::cout << " === INFO === " << std::endl;
	std::cout << r.getNChannels() << std::endl;
	std::cout << r.getSampRate() << std::endl;
	std::cout << r.getBytesPerSec() << std::endl;
	std::cout << r.getBlockAlign() << std::endl;
	std::cout << r.getBitsPerSample() << std::endl;
}
