#include "file_writing.h"

template <typename Word>
void WavFileProcessor::write_word(Word value, unsigned size)
{
    for (; size; --size, value >>= 8)
    file_stream.put( static_cast <char> (value & 0xFF) );
}

WavFileProcessor::WavFileProcessor(string Filename, int Num_channels, int Sample_rate, int Bit_depth) : filename(Filename), num_channels(Num_channels), sample_rate(Sample_rate), bit_depth(Bit_depth)
{
    file_stream.open(filename, ios::binary);
    
    file_stream << "RIFF----WAVEfmt "; //RIFF, WAVE and fmt headers, ---- size of a file (empty)
    
    write_word(16, 4); //Subchunk1Size - always at 16
    write_word(1, 2); //AudioFormat 1 - PCM
    write_word(num_channels, 2); //Number of channels (stereo)
    write_word(sample_rate, 4); //SampleRate (samples per second)
    int block_align = ((bit_depth-1)/8 + 1) * num_channels; //calculate bytes for one sample
    write_word(sample_rate*block_align, 4); //ByteRate (bytes of data per second)
    write_word(block_align, 2); //BlockAlign
    write_word(bit_depth, 2); //Bits for each channel in sample

    file_stream << "data----"; //write data header with empty space for Subchunk2Size
    
    data_chunk_pos = file_stream.tellp(); //read position where real data begins
}

WavFileProcessor::~WavFileProcessor()
{
    size_t file_length = file_stream.tellp(); //read position where data ends
    file_stream.seekp(data_chunk_pos + 4); //go back to Subchunk2Size
    write_word(file_length - data_chunk_pos + 8); //set Subchunk2Size to the size of data chunk

    file_stream.seekp(4); //go back to ChunkSize
    write_word(file_length-8, 4); //set ChunkSize to a size of entire file - 8
    file_stream.close();
}
