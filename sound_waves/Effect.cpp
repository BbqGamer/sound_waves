#include "Effect.h"

void DownSampler::applyEffect() {
    int * sampleTab = new int[source.metaData.numChannels];
    source.alterBuffor(source.metaData.getBytesPerSample());
    
    while(source.readLittleEndianToBuffor()) {
        getValuesFromFileToSampleTab(sampleTab);
        duplicateSamplesByAmount(sampleTab);
        source.skipSamples((amount-1)*source.metaData.numChannels);
    }
    delete [] sampleTab;
}

void DownSampler::getValuesFromFileToSampleTab(int * sampleTab) {
    sampleTab[0] = source.getValueFromBuffor();
    for(int channel = 1; channel < source.metaData.numChannels; channel++) {
        source.readLittleEndianToBuffor();
        sampleTab[channel] = source.getValueFromBuffor();
    }
}


void DownSampler::duplicateSamplesByAmount(int * sampleTab) {
    for(int i = 0; i < amount; i++) {
        for(int channel = 0; channel < source.metaData.numChannels; channel++) {
            writeLittleEndian(sampleTab[channel],source.metaData.getBytesPerSample());
        }
    }
}
