#pragma once
#include <stdio.h>
#include <stdlib.h>

// First, get some type definitions done, based on the original WAV specification.
// RIFF chunk defined here, as in [1]. This code is taken directly
// from that source.

typedef	int32_t DWORD;	// 32 bits
typedef unsigned char BYTE;	// 8 bits

typedef DWORD FOURCC;		// Four-character code

typedef FOURCC CKID;		// Four-character-code chunk identifier
typedef DWORD CKSIZE;		// 32-bit unsigned size value

typedef struct ck {
	CKID	ckID;		// Chunk type identifier
	CKSIZE	ckSize;		// Chunk size field (size of ckData)
	BYTE*	ckData;		// Chunk data
	ck*		next;		// Pointer to next chunk
	ck*		prev;		// Pointer to previous chunk
} CK;

// Based on https://www.lightlink.com/tjweber/StripWav/Canon.html
typedef struct fmt_ck {
	CKID 	ckID;
	CKSIZE	ckSize;
	int16_t	fmt;
	int16_t	channels;
   	int32_t	samprate;
	int32_t	bytesPerSec;
	int16_t	blockAlign;
	int16_t	bitsPerSample;
} FMT_CK;
	
CK* createChunk(CKID, CKSIZE);
int deleteChunk(CK*);
CK* readChunk(FILE*);
int writeChunk(FILE*, CK*);

// 1. https://www.aelius.com/njh/wavemetatools/doc/riffmci.pdf
