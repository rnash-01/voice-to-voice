#include <stdio.h>
#include <stdlib.h>

// First, get some type definitions done, based on the original WAV specification.
// RIFF chunk defined here, as in [1]. This code is taken directly
// from that source.

typedef unsigned long DWORD;	// 32 bits
typedef unsigned char BYTE;	// 8 bits

typedef DWORD FOURCC;		// Four-character code

typedef FOURCC CKID;		// Four-character-code chunk identifier
typedef DWORD CKSIZE;		// 32-bit unsigned size value

typedef struct {
	CKID	ckID;		// Chunk type identifier
	CKSIZE	ckSize;		// Chunk size field (size of ckData)
	BYTE*	ckData;		// Chunk data
} CK;

// createChunk
// Create unpopulated RIFF chunk.
CK* createChunk(CKID ckId, CKSIZE ckSize);

// 1. https://www.aelius.com/njh/wavemetatools/doc/riffmci.pdf
