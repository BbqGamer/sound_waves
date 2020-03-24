#include "waveform.h"
#include <cmath>

WaveForm::WaveForm(int Precision)
{
    precision = Precision;
    waveform_tab = new double[precision];
}


void WaveForm::setTab(int i, int value)
{
    waveform_tab[i] = value;
}


WaveForm create_sine(int precision)
{
    WaveForm wave(precision);
    
    double two_pi = 2 * atan(1)*4;
    
    for(int i = 0; i < precision; i++)
    {
        wave.setTab(i, sin(i * two_pi/precision));
    }
    
    return wave;
}
