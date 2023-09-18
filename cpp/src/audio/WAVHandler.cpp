#include <audio/WAVHandler.h>

/*
  loadMeta
  Loads meta information about the file, when nothing has been read yet.
  Only to be called by openFile.
 */
WAVReader::WAVReader(size_t s, std::string f) : AudioReader(s)
{
	f.copy((this->fName = new char[f.length()]), f.length(), 0);
	this->wavFile = NULL;
}
void WAVReader::loadMeta()
{
	if (!wavFile) return;
	char	temp[8] = {'\0'};
	CKID 	ckID = 0;
	CKSIZE 	ckSize = 0;

	// Read directly into ckID and ckSize
	wavFile->read((char*)&ckID, 2 * sizeof(DWORD));

	wavFile->read(temp, 4);

	if (strcmp(temp, "WAVE")) goto err;
	wavFile->read((char*)&ckID, 2 * sizeof(DWORD));

	// Read format chunk into 
	wavFile->read((char*)&(this->fmt), ckSize);

	// Finally, get the actual file size.
	wavFile->read((char*)&ckID, 2 * sizeof(DWORD));

	return;

 err:
	wavFile->close();
	wavFile = NULL;
	return;
}
void WAVReader::load()
{
	// First implementation, just run in sequence.
	// Later on, try to implement in parallel?
	uint i = 0;					// Index of buffer item

	BYTE* buffer;
	CK* ck;
	CKID ckId;
	CKSIZE ckSize;
	size_t n;

	if (!openFile()) return;
	/*	while (!threadFlag)
	{
		wavFile->read((char*)&ckId, 2 * sizeof(DWORD));
		

		if (onLoad) onLoad(buffer, n, *(this->callbackArg));
		}*/
	closeFile();
}

int WAVReader::openFile()
{
	if (wavFile) wavFile->close();
	if (!(wavFile = new std::ifstream(fName, std::ifstream::binary)) || wavFile->fail())
		return 0;

	loadMeta();
	return 1;

}

void WAVReader::closeFile()
{
	if (!wavFile) return;
	wavFile->close();
	wavFile = NULL;
}
