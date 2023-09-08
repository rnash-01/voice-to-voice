#pragma once

#include <audio/io.h>
#include <audio/AudioHandler.h>
class WAVReader : public AudioReader
{
 public:
	WAVReader() {}
	~WAVReader() {}
	
 private:
	int 		deleteChunk(CK* ck);
	CK* 		readChunk(FILE* fp);
	int 		writeChunk(FILE* fp, CK* ck);
};
