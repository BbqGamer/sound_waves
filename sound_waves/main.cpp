#include "file_writing.h"
#include "waveform.h"
#include <cmath>

int main() {
    
    int number_of_channels = 1;
    int sample_rate = 70000;
    int bit_depth = 16;
    
    WavFileProcessor file_processor("test14.wav", number_of_channels, sample_rate, bit_depth);
    
    WaveForm sine = create_sine(5000);
    
    file_processor.writeNote(sine, 880, 2, 20000);
    
    file_processor.saveFile();
        
    return 0;
}
