#include <iostream>
#include "file_writing.h"
#include <cmath>

int main() {
    
    //testing code by creation of square wave
    
    int number_of_channels = 1;
    int sample_rate = 24000;
    int bit_depth = 16;
    
    ofstream f = create_wav_file("test1.wav", number_of_channels, sample_rate, bit_depth);
    size_t data_chunk_pos = f.tellp(); //read position where real data begins
    
    int time = 2;
    int max_amplitude = pow(2,(bit_depth-1));
    cout << max_amplitude;
    int frequency = 440;
    int wavelength = sample_rate/frequency; //not realy wavelength
    
    for(int i = 0; i < time*sample_rate; i++)
    {
        if (i % wavelength > wavelength/2)
        {
            write_word(f, max_amplitude, 2);
        }
        else {
            write_word(f, 0, 2);
        }
    }
    
    complete_wav_file(f, data_chunk_pos);
    
    return 0;
}
