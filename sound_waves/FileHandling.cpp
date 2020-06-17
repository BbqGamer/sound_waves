#include "FileHandling.h"


File::File(FileLocationDetails identification)
    : identification{identification} {}

bool File::checkIfExists() {
    std::ifstream f(getPath().c_str());
    return f.good();
}

std::string File::getPath() {
    std::string path = identification.directoryPath + "/" + identification.fileName;
    if(identification.extension.length()>0) {
        path += "." + identification.extension;
    }
    return path;
}

std::ostream& operator<<(std::ostream& outs, File& fileToWrite) {
    outs << "File path: " << fileToWrite.getPath();
    if(!fileToWrite.checkIfExists()) {
        outs << std::endl << "[WARNING] This file doesn't physically exist!";
    }
    return outs;
}

void FileReader::closeIfOpen() {
    if(fileStream.is_open()) {
        fileStream.close();
    }
}

void FileReader::skipBytes(int numBytes) {
    fileStream.ignore(numBytes);
}
    
FileReader::FileReader(FileLocationDetails identification)
  : File(identification) {
    
    alterBuffor(1);
    
    try {
        fileStream.open(getPath(), std::ios::in | std::ios::binary);
    }
    catch (const std::exception)
    {
        std::cout << "[ERROR] Trouble in opening file!";
    }
}
    

int FileReader::readLittleEndianFromPositionInStream(size_t position, unsigned int size) {
    alterBuffor(size);
    return readLittleEndianFromPositionInStream(position);
}
    
int FileReader::readLittleEndianFromPositionInStream(size_t position) {
    goToPositionInStream(position);
    return readLittleEndian();
}
    
void FileReader::goToPositionInStream(size_t position) {
    fileStream.seekg(position);
}
    
void FileReader::alterBuffor(unsigned int size)
{
    deleteBufforIfExists();
    buffor = new char[size];
    bufforSize = size;
}
    
void FileReader::deleteBufforIfExists()
{
    if(!(buffor == nullptr)) {
        delete[] buffor;
    }
}

FileReader::~FileReader() {
    delete[] buffor;
    closeIfOpen();
}
    
int FileReader::readLittleEndian()
{
    readLittleEndianToBuffor();
    return getValueFromBuffor();
}

bool FileReader::readLittleEndianToBuffor()
{
    if(fileStream.read(buffor, bufforSize)) {
        return 1; //returns 1 to signify that it was read succesfully
    }
    return 0;
}
 
int FileReader::getValueFromBuffor()
{
    if(bufforSize == 1) {
        return *((char *) buffor);
    } else if (bufforSize == 2) {
        return *((short *) buffor);
    }
    return *((int*) buffor);
}


FileWriter::FileWriter(FileLocationDetails identification)
    : File(identification) {
    try {
        fileStream.open(getPath(), std::ios::out | std::ios::binary);
    }
    catch (const std::exception)
    {
        std::cout << "[ERROR] Trouble in opening file!";
    }
}
    
size_t FileWriter::getPositionInStream() {
    return fileStream.tellp();
}
    
void FileWriter::writeBigEndianString(std::string input) {
    fileStream << input;
}

FileWriter::~FileWriter() {
    closeIfOpen();
}
    
void FileWriter::goToPositionInStream(size_t position) {
    fileStream.seekp(position);
}

void FileWriter::closeIfOpen() {
    if(fileStream.is_open()) {
        fileStream.close();
    }
}
