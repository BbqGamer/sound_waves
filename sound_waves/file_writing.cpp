#include "file_writing.h"

ofstream create_wav_file(string filename, int num_channels, int sample_rate, int bit_depth)
{

    //function creates wav file and fills headers
    ofstream f(filename, ios::binary);

    f << "RIFF----WAVEfmt "; //RIFF, WAVE and fmt headers, ---- size of a file (empty)
    write_word(f, 16, 4); //Subchunk1Size - always at 16
    write_word(f, 1, 2); //AudioFormat 1 - PCM
    write_word(f, num_channels, 2); //Number of channels (stereo)
    write_word(f, sample_rate, 4); //SampleRate (samples per second)
    int block_align = ((bit_depth-1)/8 + 1) * num_channels; //calculate bytes for one sample
    write_word(f, sample_rate*block_align, 4); //ByteRate (bytes of data per second)
    write_word(f, block_align, 2); //BlockAlign
    write_word(f, bit_depth, 2); //Bits for each channel in sample

    f << "data----"; //write data header with empty space for Subchunk2Size

    return f;
}

void complete_wav_file(ofstream& f, size_t data_chunk_pos)
{
    size_t file_length = f.tellp(); //read position where data ends

    f.seekp(data_chunk_pos + 4); //go back to Subchunk2Size
    write_word(f, file_length - data_chunk_pos + 8); //set Subchunk2Size to the size of data chunk

    f.seekp(4); //go back to ChunkSize
    write_word(f, file_length-8, 4); //set ChunkSize to a size of entire file - 8
    f.close();
}


template <typename Word>
ostream& write_word(ostream& outs, Word value, unsigned size)
{
    for (; size; --size, value >>= 8)
      outs.put( static_cast <char> (value & 0xFF) );
    return outs;
}
