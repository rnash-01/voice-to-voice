#include <main.h>

/*
  Sandbox - for debugging/experimenting
*/
int main(int argc, char** argv)
{
  WAVReader r("./test.wav");
  BinaryTree b;
  r.load(b);
  std::cout << r.getSampRate() << r.getBitsPerSample() << r.getBlockAlign() << r.getBytesPerSec() << r.getNChannels() << std::endl;


	WAVWriter w(r, "./test_out.wav");
  std::cout << w.getSampRate() << w.getBitsPerSample() << w.getBlockAlign() << w.getBytesPerSec() << w.getNChannels() << std::endl;
  w.load(b);


}