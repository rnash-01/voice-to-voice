#include <audio/WAVHandler.h>

// Handler
WAVHandler::WAVHandler()
{
	this->fName 		= NULL;
	this->wavFile 		= NULL;
}

WAVHandler::~WAVHandler()
{
	if (this->fName) delete[] this->fName;
	if (this->wavFile)
	{
		this->wavFile->close();
		delete this->wavFile;
	}
}

// Reader
WAVReader::WAVReader()
{
	this->samplesPerBufItem = 1;
}

WAVReader::WAVReader(std::string f) : WAVReader()
{
	f.copy((this->fName = new char[f.length()]), f.length(), 0);
}

/*
  loadMeta
  Loads meta information about the file, when nothing has been read yet.
  Only to be called by openFile.
 */
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

	// Read format chunk into reader's format information.
	wavFile->read((char*)&(this->fmt), ckSize);

	// Finally, get the actual file size.
	wavFile->read((char*)&ckID, 2 * sizeof(DWORD));
	this->fSize = ckSize;

	return;

 err:
	wavFile->close();
	wavFile = NULL;
	return;
}

/*
  load
  Loads WAV file into b.
 */
void WAVReader::load(Buffer& b)
{
	// First implementation, just run in sequence.
	// Later on, try to implement in parallel?
	uint i = 0;					// Index of buffer item

	BYTE* buffer;
	CK* ck;
	CKID ckId;
	CKSIZE ckSize;
	size_t n;

	if (!samplesPerBufItem) return;
	if (!openFile()) 		return;

	n = samplesPerBufItem * fmt.blockAlign;
	while (!threadFlag && !wavFile->eof())
	{
		// As openFile has finished, we expect all the file
		// format information has been loaded.
		buffer = new BYTE[n];
		wavFile->read((char*)buffer, n);

		// wavFile->gcount() because we might read less than
		// the buffer size allows.
		b.appendItem(i, wavFile->gcount(), buffer);

		delete[] buffer;
		i++;
	}
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


// %% Writer %%

WAVWriter::WAVWriter()
{
	// Set defaults.
	FMT_CK& fmt		   	= this->fmt;
	fmt.fmt				= 1;
	fmt.channels		= 1;
	fmt.samprate		= 44100;
	fmt.bitsPerSample	= 16;
	fmt.blockAlign		= (fmt.bitsPerSample * fmt.channels) / 8;
	fmt.bytesPerSec		= (fmt.blockAlign * fmt.samprate);
}
/*
  Constructor
  Absorbs formatting information from h.

  @param h The handler (reader or writer) from which to copy.
 */
WAVWriter::WAVWriter(WAVHandler& h)
{
	FMT_CK& fmt 		= this->fmt;

	// Copy format information from WAVReader.
	fmt.channels		= h.getNChannels();
	fmt.samprate		= h.getSampRate();
	fmt.bytesPerSec		= h.getBytesPerSec();
	fmt.blockAlign		= h.getBlockAlign();
	fmt.bitsPerSample	= h.getBitsPerSample();
}

/*
  loadMeta
  Writes formatting chunk to file
 */
void WAVWriter::loadMeta()
{
	
}

/*
  openFile
 */
int WAVWriter::openFile()
{
}

/*
  closeFile
*/
void WAVWriter::closeFile()
{}
/*
  load
*/
void WAVWriter::load(Buffer& b)
{
	
}
