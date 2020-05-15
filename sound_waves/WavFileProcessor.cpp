#include "WavFileProcessor.h"

WavFileProcessor::WavFileProcessor(std::string FileName)
    :FileProcessor(FileName, FileProcessor::Read)
{
    file_stream.seekp(22);
    ReadWord(num_channels);
    ReadWord(sample_rate);
    file_stream.seekp(32);
    ReadWord(block_align);
    ReadWord(bit_depth);
    file_stream.seekp(44);
}


WavFileProcessor::WavFileProcessor(std::string FileName, int Num_channels, int Sample_rate, int Bit_depth) : FileProcessor(FileName), num_channels(Num_channels), sample_rate(Sample_rate), bit_depth(Bit_depth)
{
    
    file_stream << "RIFF----WAVEfmt "; //RIFF, WAVE and fmt headers, ---- size of a file (empty)
    
    WriteWord(16, 4); //Subchunk1Size - always at 16
    WriteWord(1, 2); //AudioFormat 1 - PCM
    WriteWord(num_channels, 2); //Number of channels (stereo)
    WriteWord(sample_rate, 4); //SampleRate (samples per second)
    block_align = ((bit_depth-1)/8 + 1) * num_channels; //calculate bytes for one sample
    WriteWord(sample_rate*block_align, 4); //ByteRate (bytes of data per second)
    WriteWord(block_align, 2); //BlockAlign
    WriteWord(bit_depth, 2); //Bits for each channel in sample

    file_stream << "data----"; //write data header with empty space for Subchunk2Size
    
    data_chunk_pos = file_stream.tellp(); //read position where real data begins
}


void WavFileProcessor::saveFile()
{
    size_t file_length = file_stream.tellp(); //read position where data ends
    file_stream.seekp(data_chunk_pos + 4); //go back to Subchunk2Size
    WriteWord(file_length - data_chunk_pos + 8); //set Subchunk2Size to the size of data chunk

    file_stream.seekp(4); //go back to ChunkSize
    WriteWord(file_length-8, 4); //set ChunkSize to a size of entire file - 8
    closeFile();
}


std::ostream& operator<<(std::ostream& os, WavFileProcessor& obj)
{
    os << "[File Processor Info]" << std::endl;
    os << "    File name:        " << obj.filename << std::endl;
    os << "    Processor state:  " << obj.m_state << "   (0) read / (1) write "<< std::endl;
    os << std::endl;
    os << "[Wav Params]" << std::endl;
    os << "Num channels: " << obj.num_channels << std::endl;
    os << "Sample rate:  " << obj.sample_rate << std::endl;
    os << "Block align:  " << obj.block_align << std::endl;
    os << "Bit depth:    " << obj.bit_depth << std::endl;
    
    return os;
}


/*
void WavFileProcessor::writeNote(WaveForm Waveform, double frequency, double duration, double amplitude)
{
    //TODO
    
    WaveForm waveform = Waveform;
    
    for (int i = 0; i < frequency * duration; i++)
    {
        writeWave(waveform, amplitude);
    }
}

void WavFileProcessor::writePause(double duration)
{
    for (int i = 0; i < num_channels * duration * sample_rate; i++)
    {
        write_word(0, 2);
    }
}

void WavFileProcessor::writeWave(WaveForm waveform, double amplitude)
{
    for(int i = 0; i < waveform.getPrecision(); i++)
    {
        write_word(int(waveform[i] * amplitude), 2);
        std::cout << int(waveform[i] * amplitude) << std::endl;
    }
}
*/

