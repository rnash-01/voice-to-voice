#include <test/Spectrogram.h>

TEST_F(SpectrogramTest, ConstructDestruct) {
    Spectrogram* spectrogram = new Spectrogram(10, 10);
    EXPECT_NO_FATAL_FAILURE(delete spectrogram);
}

TEST_F(SpectrogramTest, GetSet) {
    Spectrogram spectrogram(10, 10);
    spectrogram.setValue(0, 0, Complex{1, 1});
    EXPECT_EQ(spectrogram.getValue(0, 0).r, 1);
    EXPECT_EQ(spectrogram.getValue(0, 0).i, 1);
}