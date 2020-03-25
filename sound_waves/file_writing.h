#ifndef file_writing_h
#define file_writing_h

#include "waveform.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class WavFileProcessor
{
    ofstream file_stream;
    string filename;
    int num_channels;
    int sample_rate;
    int bit_depth;
    
    size_t data_chunk_pos;
    
    template <typename Word>
    void write_word(Word value, unsigned size = sizeof(Word)); //writes choosen word to binary file
    
    public:
        
        WavFileProcessor(string Filename, int Num_channels, int Sample_rate, int Bit_depth);
        ~WavFileProcessor();
    
};

#endif
