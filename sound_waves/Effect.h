#pragma once

#include "WavFileHandling.h"

class EffectApplier : public WavFileWriter {
    
public:
        
    WavFileReader& source;
    
    EffectApplier(WavFileReader& source, std::string destinationFileName);
    
    void virtual applyEffect() = 0;
};


class DownSampler : public EffectApplier {
  
    char amount;
    
public:
    
    DownSampler(WavFileReader& source, std::string destinationFileName, char amount)
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


class Gain {
    
};

