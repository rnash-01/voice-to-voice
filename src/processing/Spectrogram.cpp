#include <processing/Spectrogram.h>

Spectrogram::Spectrogram(uint frequencies, uint frames) {
    this->frequencies = frequencies;
    this->frames = frames;
    this->values = new Complex[frequencies * frames];
}

Spectrogram::~Spectrogram() {
    if (this->values)
    {
        delete[] values;
        this->values = nullptr;
    }
}