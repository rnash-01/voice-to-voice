#pragma once

#include <audio/io.h>

class AudioReader
{
 public:
	AudioReader(size_t);
	~AudioReader() { if (this->buffer) delete this->buffer; }
	void			bindLoadCallback(int (*callback)(const CK&, void*&));			// Sets onLoad
	inline size_t	getSize() { return bufferSize; }
	
 private:
	BYTE*			buffer;
	size_t			bufferSize;
	bool 			isLoading;
	int				(*onLoad)();	// When certain amount of data is loaded, call.
};


