#pragma once
#include <common.h>
typedef struct {
    float r;
    float i;
} Complex;

/**
 * Wrapper for array of Complex.
 */
class Spectrogram {
public:
    Spectrogram(uint, uint);
    ~Spectrogram();
    
    Complex getValue(uint i, uint j)                    { return values[i * frames + j]; }
    void    setValue(uint i, uint j, Complex value)     { this->values[i * frames + j] = value; }

private:
    uint frequencies;
    uint frames;
    Complex* values;
};