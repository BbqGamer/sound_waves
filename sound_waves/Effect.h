#pragma once

#include "WavFileHandling.h"

class EffectApplier : public WavFileWriter {
    
public:
        
    WavFileReader& source;
    
    EffectApplier(WavFileReader& source, FileLocationDetails destinationFile)
    : source{source}, WavFileWriter(destinationFile, source.metaData) {}
    
    void virtual applyEffect() = 0;
};


class DownSampler : public EffectApplier {
  
    char amount;
    
public:
    
    DownSampler(WavFileReader& source, FileLocationDetails destinationFile, char amount)
    : EffectApplier(source, destinationFile), amount{amount} {}
    
    void applyEffect() override;
    void getValuesFromFileToSampleTab(int * sampleTab);
    void duplicateSamplesByAmount(int * sampleTab);
};


class Gain


