#include "Effect.h"


EffectApplier::EffectApplier(WavFileReader& source, std::string destinationFileName)
: source{source}, WavFileWriter(destinationFileName, source.metaData) {
    source.alterBuffor(source.metaData.getBytesPerSample());
}


void Downsampler::applyEffect() {
    int * sampleTab = new int[source.metaData.numChannels];
    
    while(source.readLittleEndianToBuffor()) {
        getValuesFromFileToSampleTab(sampleTab);
        duplicateSamplesByAmount(sampleTab);
        source.skipSamples((amount-1)*source.metaData.numChannels);
    }
    delete [] sampleTab;
}

void Downsampler::getValuesFromFileToSampleTab(int * sampleTab) {
    sampleTab[0] = source.getValueFromBuffor();
    for(int channel = 1; channel < source.metaData.numChannels; channel++) {
        source.readLittleEndianToBuffor();
        sampleTab[channel] = source.getValueFromBuffor();
    }
}


void Downsampler::duplicateSamplesByAmount(int * sampleTab) {
    for(int i = 0; i < amount; i++) {
        for(int channel = 0; channel < source.metaData.numChannels; channel++) {
            writeLittleEndian(sampleTab[channel],source.metaData.getBytesPerSample());
        }
    }
}


void BitReductor::applyEffect() {
    while(source.readLittleEndianToBuffor())
    {
        reduceSample();
    }
}

void BitReductor::reduceSample() {
    int newValue = getReducedValue(source.getValueFromBuffor());
    writeLittleEndian(newValue, source.metaData.getBytesPerSample());
}

int BitReductor::getReducedValue(int initValue) {
    int decreasedValue = initValue/(float)source.metaData.getMaxAmplitude() * pow(2, bitAmount-1);
    decreasedValue = ceil(decreasedValue);
    return decreasedValue * source.metaData.getMaxAmplitude() / pow(2, bitAmount-1);
}


void Amplifier::applyEffect() {
    while(source.readLittleEndianToBuffor())
    {
        adjustSample();
    }
}

void Amplifier::adjustSample() {
    int newValue = source.getValueFromBuffor() * multiplier;
    if(newValue > source.metaData.getMaxAmplitude()) {
        newValue = source.metaData.getMaxAmplitude();
    }
    writeLittleEndian(newValue, source.metaData.getBytesPerSample());
}
