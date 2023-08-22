#include "io.h"
CK* createChunk(CKID ckID, CKSIZE size)
{
	BYTE* ptr;								// Pointer to chunk data
	CK* chunk = 0;							// Pointer to chunk struct
	CKSIZE chunkSize;						// Word-aligned size of chunk

	// Calculate chunkSize (number of total elements
	chunkSize = (size / sizeof(BYTE)) + 1;

	// Attempt pointer allocation
	if (!(ptr = (BYTE*) malloc(chunkSize * sizeof(DWORD))))
		return 0;
	
	// Else...
	chunk = (CK*)malloc(sizeof(CK));
	
	chunk->ckID = ckID;
	chunk->ckSize = size;
	chunk->ckData = ptr;
	
	return chunk;
}

