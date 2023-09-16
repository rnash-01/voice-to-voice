#pragma once

#include <common.h>
#include <audio/io.h>
#include <data/Buffer.h>

class AudioReader
{
 public:
	AudioReader(size_t);
	~AudioReader() { if (this->buffer) delete[] this->buffer; }

	void			bindLoadCallback(int (*callback)(AudioReader*, Buffer&), Buffer&);
	inline 	size_t	getSize() { return bufferSize; }
	void			startLoad();	// Starts loading procedure
	void			stopLoad();	// Stops loading procedure
	
 protected:
	BYTE*			buffer;
	size_t			bufferSize;
	bool 			isLoading;
	bool			threadFlag;
	void			threadLoad();
	virtual void	load() = 0; 						// specific to subclass
	int				(*onLoad)(AudioReader*, Buffer&);	// When certain amount of data is loaded, call.
	Buffer*			callbackArg;						// Buffer used in the callback.
	std::thread* 	control;
};


