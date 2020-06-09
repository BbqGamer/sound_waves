#include "WavFileHandling.h"


WavFileReader::WavFileReader(FileLocationDetails identification)
: FileReader(identification) {
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


WavFileWriter::WavFileWriter(FileLocationDetails identification, WavInfo metaData)
: FileWriter(identification), metaData{metaData} {
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
    writeLittleEndian(metaData.getBytesPerSample(),2);
    writeLittleEndian(metaData.bitDepth,2);
    writeBigEndianString("data----");
}

void WavFileWriter::completeHeadersAndSave() {
    size_t fileLength = getPositionInStream();
    goToPositionInStream(data_chunk_pos + 4);
    writeLittleEndian(fileLength - data_chunk_pos + 8);
    goToPositionInStream(4);
    writeLittleEndian(fileLength-8,4);
    closeIfOpen();
}

WavFileWriter::~WavFileWriter() {
    completeHeadersAndSave();
}
