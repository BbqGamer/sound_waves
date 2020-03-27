#include "file_writing.h"
#include "waveform.h"
#include <cmath>

int main() {
    
    int number_of_channels = 1;
    int sample_rate = 70000;
    int bit_depth = 16;
    
    WavFileProcessor file_processor("test14.wav", number_of_channels, sample_rate, bit_depth);
    
    WaveForm sine = create_sine(5000);
    
    file_processor.writeNote(sine, 196, 0.25, 20000);
    file_processor.writeNote(sine, 220, 0.25, 20000);
    file_processor.writeNote(sine, 233, 0.25, 20000);
    file_processor.writeNote(sine, 265, 0.25, 20000);
    file_processor.writeNote(sine, 220, 0.5, 20000);
    file_processor.writeNote(sine, 174, 0.25, 20000);
    file_processor.writeNote(sine, 196, 1, 20000);
    
    
    
    file_processor.saveFile();
        
    return 0;
}
