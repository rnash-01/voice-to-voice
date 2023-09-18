#include <main.h>

/*
  Sandbox - for debugging/experimenting
*/
int main(int argc, char** argv)
{
	WAVReader r(0, "./test.wav");
	r.load();
}
