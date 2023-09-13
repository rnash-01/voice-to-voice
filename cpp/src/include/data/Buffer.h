#pragma once

#include <common.h>
#include <audio/io.h>


/*
  Buffer acts as an interface.
As of right now, the "best implementation" of the
buffer containing full audio data from which
FFTs are produced is not really known, and
might vary based on context. So, just a catch-all
buffer interface which can be implemented as a binary tree
for file I/O and as a linked list for live device I/O (I make the
assumption that for live I/O, non-locking synchronisation is needed,
so the binary tree's property of having an inherent order is not needed
since the linked list will be updated in the correct order anyway, whereas
this is not strictly the case with file I/O
*/

class Buffer
{
 public:
	Buffer() {}
	~Buffer() {}
	virtual BYTE 	operator[](uint) 					= 0;
	virtual BYTE* 	readBetween(uint, uint) 			= 0;
	virtual void	appendItem(uint, size_t, BYTE*) 	= 0;

 protected:
	void* first;
};


