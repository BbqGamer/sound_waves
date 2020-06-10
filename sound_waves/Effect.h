#pragma once

#include "WavFileHandling.h"

class EffectApplier : public WavFileWriter {
    
public:
        
    WavFileReader& source;
    
    EffectApplier(WavFileReader& source, std::string destinationFileName)
    : source{source}, WavFileWriter(destinationFileName, source.metaData) {}
    
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


class Gain {
    
};

