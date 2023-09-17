#include <audio/WAVHandler.h>

void WAVReader::load()
{
	// First implementation, just run in sequence.
	// Later on, try to implement in parallel?
	openFile();
	while (!threadFlag)
	{
		// Read one chunk at a time into the buffer.
		
	}
	closeFile();
}

void WAVReader::openFile()
{
}

void WAVReader::closeFile()
{
}
