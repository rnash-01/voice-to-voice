#pragma once

#include <audio/io.h>
#include <audio/AudioHandler.h>


class WAVReader : public AudioReader
{
 public:
	WAVReader(size_t s) : AudioReader(s) { this->fName = NULL; this->wavFile = NULL; }
	WAVReader(size_t s, std::string f);

	void load(Buffer&) override;

	inline int16_t getNChannels		()	{ return fmt.channels; 		}
	inline int32_t getSampRate		()	{ return fmt.samprate; 		}
	inline int32_t getBytesPerSec	() 	{ return fmt.bytesPerSec; 	}
	inline int16_t getBlockAlign	()	{ return fmt.blockAlign;	}
	inline int16_t getBitsPerSample	()	{ return fmt.bitsPerSample;	}

	
 private:
	int openFile();
	void closeFile();
	void loadMeta();

	std::ifstream* wavFile;
	char* fName;
	size_t fSize;
	FMT_CK fmt;				// contains meta info about the file. E.g., sample rate, number of channels, etc.
	
};
