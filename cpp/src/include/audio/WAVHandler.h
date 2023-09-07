#pragma once

#include <audio/io.h>

class AudioHandler
{
 public:
	AudioHandler() {}
	~AudioHandler() {}
 
	inline bool isLoading() { return loading; }
	void 		onLoad(const& int (callback)());
	
 private:
	CK* 		createChunk(CKID ckId, CKSIZE ckSize);
	int 		deleteChunk(CK* ck);
	CK* 		readChunk(FILE* fp);
	int 		writeChunk(FILE* fp, CK* ck);

	bool 		loading;										// Buffer being updated?
	CK*			buffer;											// Linked List buffer
};
