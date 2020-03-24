#include "waveform.h"
#include <cmath>
#include <iostream>

WaveForm::WaveForm(int Precision)
{
    precision = Precision;
    waveform_tab = new double[precision];
}


void WaveForm::setTab(int i, double value)
{
    waveform_tab[i] = value;
}


double WaveForm::operator[](int i)
{
    return waveform_tab[i];
}


WaveForm create_sine(int precision)
{
    WaveForm wave(precision);
    
    double two_pi = 6.283;
    
    for(int i = 0; i < precision; i++)
    {
        wave.setTab(i, sin(i * two_pi/(double)precision));
    }
    
    return wave;
}
