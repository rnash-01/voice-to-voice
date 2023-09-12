#include <audio/AudioHandler.h>

AudioReader::AudioReader(size_t bufferSize)
{
	this->bufferSize = 0;
	this->buffer = (BYTE*) 0;
	if ((this->buffer = new BYTE[bufferSize]))
		this->bufferSize = bufferSize;  	
}
