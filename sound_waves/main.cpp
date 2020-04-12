#include "file_writing.h"
#include "waveform.h"
#include <cmath>
#include "tests.h"

int main() {
    
    RunTests();
    
    int number_of_channels = 1;
    int sample_rate = 70000;
    int bit_depth = 16;
    
    WavFileProcessor file_processor("test14.wav", number_of_channels, sample_rate, bit_depth);
    
    WaveForm sine = create_sine(5000);
    
    //play lick
    file_processor.writeNote(sine, 392, 0.25, 20000);
    file_processor.writeNote(sine, 440, 0.25, 20000);
    file_processor.writeNote(sine, 466, 0.25, 20000);
    file_processor.writeNote(sine, 532, 0.25, 20000);
    file_processor.writeNote(sine, 440, 0.5, 20000);
    file_processor.writeNote(sine, 349, 0.25, 20000);
    file_processor.writeNote(sine, 392, 0.25, 20000);
    

    file_processor.saveFile();
        
    return 0;
}
