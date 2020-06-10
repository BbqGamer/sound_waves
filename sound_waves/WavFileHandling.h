#pragma once
#include "FileHandling.h"
#include <math.h>


struct WavInfo
{
    short numChannels;
    int sampleRate;
    short bitDepth;
    
    int getBytesPerSampleTimesChannles() {
        return getBytesPerSample() * numChannels;
    }
    
    int getBytesPerSample() {
        return ((bitDepth-1)/8 + 1);
    }
    
    int getByteRate() {
        return getBytesPerSample() * sampleRate;
    }
    
    int getMaxAmplitude() {
        return pow(2, bitDepth-1);
    }
};


class WavFileReader : public FileReader
{
public:
    WavInfo metaData;
    size_t data_chunk_pos;
    
    WavFileReader();
    
    
public:
    
    WavFileReader(std::string fileName, std::string directoryPath = "./inputSamples");
    void readHeaders();
    
    void skipSamples(int numSamples);
    
    void goToDataStart();
    
};


class WavFileWriter : public FileWriter
{
    WavInfo metaData;
    size_t data_chunk_pos;
    
    void writeHeaders();
    void completeHeadersAndSave();
    
    WavFileWriter();
    
public:
    WavFileWriter(std::string fileName, WavInfo metaData);
    
    ~WavFileWriter();
    
    
};
