#pragma once

#include <audio/io.h>
#include <audio/AudioHandler.h>


class WAVReader : public AudioReader
{
 public:
	WAVReader(size_t s);
	WAVReader(size_t s, std::string f);

	void load(Buffer&) override;

	inline int16_t 	getNChannels		   		()			{ return fmt.channels; 			}
	inline int32_t 	getSampRate				   	()			{ return fmt.samprate; 			}
	inline int32_t 	getBytesPerSec				() 			{ return fmt.bytesPerSec; 		}
	inline int16_t 	getBlockAlign				()			{ return fmt.blockAlign;		}
	inline int16_t 	getBitsPerSample			()			{ return fmt.bitsPerSample;		}
	inline size_t	getFSize					()			{ return fSize;					}

	inline void		setSamplesPerBufItem		(size_t n)	{ this->samplesPerBufItem = n; 	}

	
 private:
	int openFile();
	void closeFile();
	void loadMeta();

	std::ifstream* wavFile;
	char* fName;
	size_t fSize;
	FMT_CK fmt;				// contains meta info about the file. E.g., sample rate, number of channels, etc.
	size_t samplesPerBufItem;
	
};
