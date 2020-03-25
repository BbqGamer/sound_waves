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


int WaveForm::getPrecision()
{
    return precision;
}


WaveForm create_sine(int precision)
{
    WaveForm wave(precision);
    
    const long double PI = 3.14159265359;
    
    for (int i = 0; i < precision; i++)
    {
        wave.setTab(i, sin(2 * PI / precision * i));
    }
    
    return wave;
}
