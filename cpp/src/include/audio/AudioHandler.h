#pragma once

#include <audio/io.h>

class AudioReader
{
 public:
	AudioReader() {}
	~AudioReader() {}
	void 	readBytes(size_t n);							// Read from buffer
	void 	bindLoadCallback(int (*callback)());			// Sets onLoad


 private:
	CK*		buffer;
	size_t	buffer_size;
	bool 	isLoading;
	int		(*onLoad)();	// When certain amount of data is loaded, call.
};


