#include <math.h>
#include "Effect.h"

int main() {
    

    WavFileReader source("melody");
    DownSampler destination(source, "melody2", 8);
    destination.applyEffect();
    
    
  
    
    /*
    WavFileProcessor f1("melody.wav");
    //WavFileProcessor f2("melodycopy.wav", f1.num_channels, f1.sample_rate, f1.bit_depth);
    
    DownSampler * ds = new DownSampler(f1, "downsample", 2);
    
    ds->apply();
    for(int i = 0; i < 100000; i++)
        ds->file_stream << 100;
    std::cout << &ds->source.file_stream << std::endl;
    std::cout << &ds->file_stream << std::endl;
    
    delete ds;
    
    
     DOWNSAMPLE
    short buffor1;
    short buffor2;
    
    while(f1.ReadWord(buffor1))
    {
        f1.ReadWord(buffor2);
        
        for(int i = 0; i < 8; i++)
        {
            f2.WriteWord(buffor1);
            f2.WriteWord(buffor2);
        }
        
        f1.SkipSamples(7);
    }
        
    
    std::cout << f1;
    std::cout << f2;
    
    
    /*
     BIT REDUCTION
    short buffor;
    float smallest_val;

    short rounded_val;
    
    short new_value;
    while(f1.ReadWord(buffor))
    {
        smallest_val = buffor/32768.0f;
        rounded_val = ceil(smallest_val);
        
        new_value = rounded_val * pow(2,15);
        f2.WriteWord(new_value);
    }
    */
}
