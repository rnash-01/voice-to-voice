#include <audio/WAVHandler.h>

// Handler
WAVHandler::WAVHandler()
{
	this->fName 		= NULL;
}

void WAVHandler::setFName(std::string fName)
{
	fName.copy((this->fName = new char[fName.length()]), fName.length(), 0);
}

// Reader
WAVReader::WAVReader()
{
	this->samplesPerBufItem = 1;
	this->wavFile = NULL;
}

WAVReader::WAVReader(std::string f) : WAVReader()
{
	this->setFName(f);
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
	buffer = new BYTE[n];
	
	while (!threadFlag && !wavFile->eof())
	{
		// As openFile has finished, we expect all the file
		// format information has been loaded.	
		wavFile->read((char*)buffer, n);

		// wavFile->gcount() because we might read less than
		// the buffer size allows.
		b.appendItem(i, wavFile->gcount(), buffer);

		i++;
	}
	
	delete[] buffer;
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



/* setDefaults
   Sets the default values for a handler.
 */
void WAVHandler::setDefaults()
{
	FMT_CK& fmt		   	= this->fmt;
	fmt.fmt				= 1;
	fmt.channels		= 1;
	fmt.samprate		= 44100;
	fmt.bitsPerSample	= 16;

	this->updateBlockAlign();
	this->updateBytesPerSec();

}

// %% Writer %%

WAVWriter::WAVWriter()
{
	this->wavFile = NULL;
	this->setDefaults();

}
WAVWriter::WAVWriter(std::string fName) : WAVWriter()
{
	this->setFName(fName);
}
/*
  Constructor
  Absorbs formatting information from h.

  @param h The handler (reader or writer) from which to copy.
 */
WAVWriter::WAVWriter(WAVHandler& h, std::string fName)
{
	this->wavFile = NULL;
	this->setFName(fName);
	
	FMT_CK& fmt 		= this->fmt;

	// Copy format information from WAVReader.
	fmt.fmt				= h.getFmt();
	fmt.channels		= h.getNChannels();
	fmt.samprate		= h.getSampRate();
	fmt.bytesPerSec		= h.getBytesPerSec();
	fmt.blockAlign		= h.getBlockAlign();
	fmt.bitsPerSample	= h.getBitsPerSample();
}

/*
  Destructor
 */
WAVWriter::~WAVWriter()
{
	if (this->wavFile != NULL) this->wavFile->close();
}

/*
  setNChannels
*/
void WAVWriter::setNChannels(int16_t channels)
{
	this->fmt.channels = channels;

	this->updateBlockAlign();
	this->updateBytesPerSec();
}

/*
  setSampRate
*/
void WAVWriter::setSampRate(int32_t samprate)
{
	this->fmt.samprate = samprate;

	this->updateBlockAlign();
	this->updateBytesPerSec();
}

/*
  setBytesPerSec
*/
void WAVWriter::setBitsPerSample(int32_t bitsPerSample)
{
	this->fmt.bitsPerSample = bitsPerSample;

	this->updateBlockAlign();
	this->updateBytesPerSec();
}

/*
  loadMeta
  Writes formatting chunk to file
 */
void WAVWriter::loadMeta()
{
	char fmtChunkSize[4]; // 16
	char dataChunkSize[4]; // 0

	// Unclean version
	// *(&fmtChunkSize[0]) = 0x10000000;

	// Clean version
	fmtChunkSize[0] = 0x10;
	fmtChunkSize[1] = 0x00;
	fmtChunkSize[2] = 0x00;
	fmtChunkSize[3] = 0x00;
	
	if (this->wavFile)
	{
		// "RIFF" chunk
		this->wavFile->write("RIFF", 4);
		this->wavFile->write(dataChunkSize, 4);			// 0 as we don't yet know the size of the file.
		this->wavFile->write("WAVE", 4);

		// "fmt " sub-chunk
		this->wavFile->write("fmt ", 4);
		this->wavFile->write(fmtChunkSize, 4);
		this->wavFile->write((char*)(&this->fmt), 16);

		// "data" sub-chunk
		this->wavFile->write("data", 4);
		this->wavFile->write(dataChunkSize, 4);
	}
}

/*
  openFile
 */
int WAVWriter::openFile()
{
	closeFile();
	if (!(this->wavFile = new std::ofstream(this->fName)) || this->wavFile->fail())
	{
		this->wavFile = NULL;
		return 0;
	}
	return 1;
}

/*
  closeFile

  Refactor - duplicate from WAVReader.
*/
void WAVWriter::closeFile()
{
	if (!wavFile) return;
	wavFile->close();
	wavFile = NULL;
}

/*
  load
*/
void WAVWriter::load(Buffer& b)
{
	char fileSize[4];

	if (&b == NULL) return;
	this->openFile();
	loadMeta();
	
	((int32_t*)fileSize)[0] = 36 + b.getSize();

	if (this->wavFile->seekp(4, std::ios_base::beg) && this->wavFile->fail()) goto end;
	this->wavFile->write(fileSize, 4);

	*fileSize = b.getSize();
	if (this->wavFile->seekp(40, std::ios_base::beg) && this->wavFile->fail()) goto end;
	this->wavFile->write(fileSize, 4);

	// Now get onto writing the data
	if (this->wavFile->seekp(0, std::ios_base::end) && this->wavFile->fail()) goto end;
	this->wavFile->write((char*)(b.readBetween(0, b.getSize())), b.getSize());
	
end:
	this->closeFile();
}
