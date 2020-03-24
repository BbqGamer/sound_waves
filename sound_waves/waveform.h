#ifndef waveform_h
#define waveform_h

class WaveForm
{
    
int precision;
double * waveform_tab;
    
public:
    
    WaveForm(int Precision);
    
    void setTab(int i, int value);
    
};

WaveForm create_sine(int precision);

#endif
