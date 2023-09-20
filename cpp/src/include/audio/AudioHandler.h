#pragma once

#include <common.h>
#include <audio/io.h>
#include <data/Buffer.h>

class AudioReader
{
 public:
	AudioReader(size_t);
	~AudioReader() { if (this->buffer) delete[] this->buffer; }

	void			bindLoadCallback(int (*callback)(BYTE*, size_t));
	inline 	size_t	getSize() { return bufferSize; }
	void			startLoad(Buffer&);	// Starts loading procedure
	void			stopLoad();		// Stops loading procedure
	
 protected:
	BYTE*			buffer;
	size_t			bufferSize;
	bool 			isLoading;
	bool			threadFlag;
	void			threadLoad(Buffer&);
	virtual void	load(Buffer&) = 0;					// specific to subclass
	int				(*onLoad)(BYTE*, size_t);			// When certain amount of data is loaded, call.
	std::thread* 	control;
};


