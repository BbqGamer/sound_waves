#include "file_writing.h"
#include "waveform.h"
#include <cmath>

int main() {
    
    //testing code by creation of square wave
    
    int number_of_channels = 1;
    int sample_rate = 24000;
    int bit_depth = 16;
    
    WavFileProcessor file_processor("test14.wav", number_of_channels, sample_rate, bit_depth);
    file_processor.~WavFileProcessor();
    

    
    /*
    ofstream f = create_wav_file("test1.wav", number_of_channels, sample_rate, bit_depth);
    
    
    size_t data_chunk_pos = f.tellp(); //read position where real data begins
    
    int time = 3;
    int max_amplitude = pow(2,(bit_depth-1));
    
    WaveForm waveform = create_sine(100);
    for(int i = 0; i < time*sample_rate; i++)
    {
        write_word(f, int((waveform[i%100]) * max_amplitude), 2);
    }
    
    complete_wav_file(f, data_chunk_pos);
    */
    
    return 0;
}
