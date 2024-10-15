#pragma once
#include <data/Buffer.h>
#include <processing/Processing.h>
#include <processing/Spectrogram.h>
#include <vector>

class Processing {
public:
    static std::vector<Spectrogram> fft(Buffer& buffer);
};