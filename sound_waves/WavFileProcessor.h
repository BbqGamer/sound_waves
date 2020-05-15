#pragma once

#include "FileProcessor.h"

class WavFileProcessor : public FileProcessor
{
    //THIS IS USED TO READ/WRITE WAV FILES
    
public:
    
    //audio params
    short num_channels;
    int sample_rate;
    short block_align; //number of bytes per sample
    short bit_depth;
    
    //position of data chunk in the file
    size_t data_chunk_pos;
    
    //open existing wav file
    WavFileProcessor(std::string Filename);
    
    //write a new wav file
    WavFileProcessor(std::string Filename, int Num_channels, int Sample_rate, int Bit_depth);

    //writes closing headers
    void saveFile();
    
    friend std::ostream& operator<<(std::ostream& os, WavFileProcessor& obj);
    
    /*
     TODO
    void writeNote(WaveForm waveform, double frequency, double duration, double amplitude);
    
    void writePause(double duration);

    void writeWave(WaveForm Waveform, double amplitude);
     */

};

std::ostream& operator<<(std::ostream& os, WavFileProcessor& obj);
