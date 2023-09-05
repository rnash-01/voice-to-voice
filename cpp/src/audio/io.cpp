#include <audio/io.h>
CK* createChunk(CKID ckID, CKSIZE size)
{
	BYTE* ptr;								// Pointer to chunk data
	CK* chunk = 0;							// Pointer to chunk struct
	CKSIZE chunkSize;						// Word-aligned size of chunk
	int i = 0;

	// Calculate chunkSize (number of total elements)
	// "A pad byte with zero is written after ckData. Word aligning
	// improves access speeds ... "
	chunkSize = size + (size % 2);
	fprintf(stdout, "Hello, chunk size is %ld\n", chunkSize);
	
	// Attempt pointer allocation
	if (!(ptr = (BYTE*) malloc(chunkSize)))
		return 0;
	
	chunk = (CK*) malloc(sizeof(CK));
	
	chunk->ckID = ckID;
	chunk->ckSize = size;
	chunk->ckData = ptr;

	// Set data to zero.
	for (i = 0; i < chunkSize; i++) ptr[i] = 0;
	
	return chunk;
}

int deleteChunk(CK* ck)
{
	if (!ck) return 1;

	if (ck->ckData) free(ck->ckData);
	free(ck);

	return 0;
}

CK* readChunk(FILE* fp)
{
	CKID 	id;
	CKSIZE 	size;
	CK*		chunk;

	// Basic checks
	if (!fp) return 0;

	// First, get chunk size, ID, etc.
	if (!fread(&id, 4, 1, fp)) return 0;
	if (!fread(&size, 4, 1, fp)) return 0;
	if (size == 0) return 0;

	// Now create a chunk based on this info
	chunk = createChunk(id, size);

	// Load the chunk with the data
	if (!fread(chunk->ckData, 1, (size + (size % 2)), fp))
	{
		deleteChunk(chunk);
		return 0;
	}

	return chunk;
}

int writeChunk(FILE* fp, CK* ck)
{
	if (!fp) return 1;

	// Write metadata first
	
	return 0;
}
