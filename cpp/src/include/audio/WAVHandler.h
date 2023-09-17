#pragma once

#include <audio/io.h>
#include <audio/AudioHandler.h>
class WAVReader : public AudioReader
{
 public:
	WAVReader(size_t s) : AudioReader(s) { this->fName = NULL; }
	WAVReader(size_t s, char** f) : AudioReader(s) { this->fName = f; }

	void load() override;
	
 private:
	void openFile();
	void closeFile();
	FILE* wavFile;
	char** fName;
};
