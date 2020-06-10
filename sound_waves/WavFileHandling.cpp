#include "WavFileHandling.h"


WavFileReader::WavFileReader(std::string fileName)
: FileReader({fileName, "wav", "./inputSamples"}) {
    readHeaders();
    goToDataStart();
}

void WavFileReader::readHeaders() {
    metaData.numChannels = readLittleEndianFromPositionInStream(22,2);
    metaData.bitDepth = readLittleEndianFromPositionInStream(34);
    metaData.sampleRate = readLittleEndianFromPositionInStream(24,4);
}
   
void WavFileReader::goToDataStart() {
    goToPositionInStream(44);
}

void WavFileReader::skipSamples(int numSamples) {
    skipBytes(metaData.getBytesPerSample() * numSamples);
}

WavFileWriter::WavFileWriter(std::string fileName, WavInfo metaData)
: FileWriter({fileName, "wav", "./outputSamples"}), metaData{metaData} {
    writeHeaders();
    data_chunk_pos = getPositionInStream();
}

void WavFileWriter::writeHeaders()
{
    writeBigEndianString("RIFF----WAVEfmt "); //leaves ---- space to complete later
    writeLittleEndian(16, 4);
    writeLittleEndian(1, 2);
    writeLittleEndian(metaData.numChannels, 2);
    writeLittleEndian(metaData.sampleRate, 4);
    writeLittleEndian(metaData.getByteRate(),4);
    writeLittleEndian(metaData.getBytesPerSampleTimesChannles(),2);
    writeLittleEndian(metaData.bitDepth,2);
    writeBigEndianString("data----");
}

WavFileWriter::~WavFileWriter() {
    completeHeadersAndSave();
}

void WavFileWriter::completeHeadersAndSave() {
    size_t fileLength = getPositionInStream();
    goToPositionInStream(data_chunk_pos + 4);
    writeLittleEndian(fileLength - data_chunk_pos + 8);
    goToPositionInStream(4);
    writeLittleEndian(fileLength-8,4);
    closeIfOpen();
}
