#pragma once

#include <audio/io.h>
#include <audio/AudioHandler.h>

class WAVHandler
{
public:
	WAVHandler									();
	~WAVHandler 								();

	inline int16_t 	getNChannels		   		()					{ return fmt.channels; 			}
	inline int32_t 	getSampRate				   	()					{ return fmt.samprate; 			}
	inline int32_t 	getBytesPerSec				() 					{ return fmt.bytesPerSec; 		}
	inline int16_t 	getBlockAlign				()					{ return fmt.blockAlign;		}
	inline int16_t 	getBitsPerSample			()					{ return fmt.bitsPerSample;		}

	
protected:
	char* 			fName;						// Name
	FMT_CK 			fmt;						// Format info (e.g., sample rate)
	std::ifstream* 	wavFile;					// File stream reader/writer

	virtual int 	openFile					() 					= 0;
	virtual void	closeFile					()					= 0;
	virtual	void	loadMeta					()					= 0;
};

class WAVReader : public WAVHandler, public	AudioReader
{
 public:
	/**/			WAVReader					();
	/**/			WAVReader					(std::string);
	/**/			~WAVReader					()					{}

	void 			load						(Buffer&) 			override;
	inline size_t	getFSize					()					{ return fSize;					}
	inline void		setSamplesPerBufItem		(size_t n)			{ this->samplesPerBufItem = n; 	}

 private:
	int 			openFile					() 					override;
	void 			closeFile					() 					override;
	void 			loadMeta					()					override;

	size_t 			fSize;						// Size of input file.											
	size_t 			samplesPerBufItem;			// How many samples of audio to store in one Buffer item.
};


/*
  WAVWriter
  Write WAV outputs from an input Buffer.
 */
class WAVWriter : public WAVHandler, public AudioWriter
{
public:
	/**/			WAVWriter					();
	/**/			~WAVWriter					() 					{}
	/**/			WAVWriter					(WAVHandler&);

	void			load						(Buffer&);

private:
	int 			openFile					() 					override;
	void 			closeFile					() 					override;
	void 			loadMeta					()					override;
	
};
