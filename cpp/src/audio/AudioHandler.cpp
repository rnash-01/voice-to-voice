#include <audio/AudioHandler.h>

AudioReader::AudioReader(size_t bufferSize)
{
	this->control = NULL;
	this->threadFlag = false;
	this->onLoad = NULL;
	this->buffer = NULL;
	this->bufferSize = 0;
	
	if (bufferSize != 0 && (this->buffer = new BYTE[bufferSize]))
		this->bufferSize = bufferSize;
	
	return;

}

void AudioReader::bindLoadCallback(int (*callback)(BYTE*, size_t, Buffer&), Buffer& arg)
{
	this->onLoad = callback;
	this->callbackArg = &arg;
}

void AudioReader::threadLoad()
{
	this->load();
}

void AudioReader::startLoad()
{
	this->isLoading = true;
	std::thread* control = new std::thread(&AudioReader::threadLoad, this);
	this->control = control;
}

void AudioReader::stopLoad()
{
	this->threadFlag = true;
	this->control->join();
	this->threadFlag = false;
	this->control = NULL;
	this->isLoading = false;
}

