#include <audio/AudioHandler.h>

AudioHandler::AudioHandler()
{
	this->control = NULL;
	this->threadFlag = false;
	this->onLoad = NULL;	
	
	return;

}

AudioHandler::~AudioHandler()
{
	if (this->control) control->join();	
}

void AudioHandler::bindLoadCallback(int (*callback)(BYTE*, size_t))
{
	this->onLoad = callback;
}

void AudioHandler::threadLoad(Buffer& b)
{
	this->load(b);
}

void AudioHandler::startLoad(Buffer& b)
{
	this->isLoading = true;
	std::thread* control = new std::thread(&AudioReader::threadLoad, this, std::ref(b));
	this->control = control;
}

void AudioHandler::stopLoad()
{
	this->threadFlag = true;
	this->control->join();
	this->threadFlag = false;
	this->control = NULL;
	this->isLoading = false;
}

