#pragma once

#include <common.h>
#include <audio/io.h>
#include <data/Buffer.h>
class AudioHandler
{
public:
	AudioHandler();
	~AudioHandler();
	void			startLoad(Buffer&);
	void			stopLoad();
	void			bindLoadCallback(int (*callback)(BYTE*, size_t));
protected:
	bool 			isLoading;
	bool			threadFlag;
	void			threadLoad(Buffer&);
	virtual void	load(Buffer&) = 0;					// specific to subclass
	int				(*onLoad)(BYTE*, size_t);			// When certain amount of data is loaded, call.
	std::thread* 	control;
};

class AudioReader : public AudioHandler
{
 public:
	AudioReader() {}
	~AudioReader() {}
	
 protected:

	virtual	void	load(Buffer&) = 0;
};

class AudioWriter : public AudioHandler
{
public:
	AudioWriter() {}
	~AudioWriter() {}

protected:
	virtual void	load (Buffer&) = 0;
	
};
