#pragma once
#include "FileHandling.h"
#include <math.h>


struct WavInfo
{
    short numChannels;
    int sampleRate;
    short bitDepth;
    
    int getBytesPerSample() {
        return ((bitDepth-1)/8 + 1) * numChannels;
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
    
    WavFileReader(FileLocationDetails identification);
    void readHeaders();
    
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
    WavFileWriter(FileLocationDetails identification, WavInfo metaData);
    
    ~WavFileWriter();
    
    
};
