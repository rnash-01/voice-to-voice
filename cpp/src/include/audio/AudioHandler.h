#pragma once

#include <common.h>
#include <audio/io.h>
#include <data/Buffer.h>

/**
 * Possibly useless :P - but just in case there's something in common between AudioReader and AudioWriter.
 */
class AudioHandler
{
public:
	AudioHandler() {};
	~AudioHandler() {};
protected:
	virtual void	load(Buffer&) = 0;					// specific to subclass
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
