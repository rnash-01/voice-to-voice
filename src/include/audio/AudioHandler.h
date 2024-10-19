#pragma once

#include <common.h>
#include <audio/io.h>
#include <data/Buffer.h>

class AudioReader
{
 public:
	AudioReader() {}
	~AudioReader() {}
	
 protected:

	virtual	void	load(Buffer&) = 0;
};

class AudioWriter
{
public:
	AudioWriter() {}
	~AudioWriter() {}

protected:
	virtual void	load (Buffer&) = 0;
	
};
