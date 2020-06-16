#pragma once

#include "WavFileHandling.h"

class EffectApplier : public WavFileWriter {
    
public:
        
    WavFileReader& source;
    
    EffectApplier(WavFileReader& source, std::string destinationFileName);
    
    void virtual applyEffect() = 0;
};


class Downsampler : public EffectApplier {
  
    char amount;
    
public:
    
    Downsampler(WavFileReader& source, std::string destinationFileName, char amount)
    : EffectApplier(source, destinationFileName), amount{amount} {}
    
    void applyEffect() override;
    void getValuesFromFileToSampleTab(int * sampleTab);
    void duplicateSamplesByAmount(int * sampleTab);
};


class BitReductor : public EffectApplier {
    
    char bitAmount;
    
public:
    
    BitReductor(WavFileReader& source, std::string destinationFileName, char bitAmount)
    : EffectApplier(source, destinationFileName), bitAmount{bitAmount} {}
    
    void applyEffect() override;

private:
    void reduceSample();
    int getReducedValue(int initValue);
    
};


class Amplifier : public EffectApplier {
    
    float multiplier;
    
public:
    
    Amplifier(WavFileReader& source, std::string destinationFileName, float multiplier)
    : EffectApplier(source, destinationFileName), multiplier{multiplier} {}
    
    void applyEffect() override;
    
private:
    void adjustSample();
    
};

