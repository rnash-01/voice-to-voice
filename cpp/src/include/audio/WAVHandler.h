#pragma once

#include <audio/io.h>
#include <audio/AudioHandler.h>

class WAVHandler
{
public:
	WAVHandler									();
	~WAVHandler 								()					{}

	inline int16_t 	getNChannels		   		()					{ return fmt.channels; 			}
	inline int32_t 	getSampRate				   	()					{ return fmt.samprate; 			}
	inline int32_t 	getBytesPerSec				() 					{ return fmt.bytesPerSec; 		}
	inline int16_t 	getBlockAlign				()					{ return fmt.blockAlign;		}
	inline int16_t 	getBitsPerSample			()					{ return fmt.bitsPerSample;		}

	void			setFName					(std::string);

	
protected:
	char* 			fName;						// Name
	FMT_CK 			fmt;						// Format info (e.g., sample rate)
	void*			wavFile;

	virtual int 	openFile					() 					= 0;
	virtual void	closeFile					()					= 0;
	virtual	void	loadMeta					()					= 0;

	void			setDefaults					();
	inline void		updateBlockAlign			()					{ fmt.blockAlign 	= (fmt.bitsPerSample * fmt.channels) / 8; 	}
	inline void		updateBytesPerSec			()					{ fmt.bytesPerSec 	= (fmt.blockAlign * fmt.samprate); 			}
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

 protected:
 	std::ifstream* 	wavFile;					// File stream reader

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
	/**/			~WAVWriter					();
	/**/			WAVWriter					(std::string);
	/**/			WAVWriter					(WAVHandler&, std::string);
	
	void			load						(Buffer&);

	void 			setNChannels		   		(int16_t);
	void 			setSampRate				   	(int32_t);
	void		 	setBitsPerSample			(int32_t);
	

protected:
	std::ofstream* 	wavFile;					// File stream writer

private:
	int 			openFile					() 					override;
	void 			closeFile					() 					override;
	void 			loadMeta					()					override;


	
};
