#include "FileHandling.h"

File::File(FileLocationDetails identification)
    : identification{identification} {}

bool File::checkIfExists() {
    std::ifstream f(getPath().c_str());
    return f.good();
}

std::string File::getFileName() {
    return identification.fileName;
}

std::string File::getDirectoryPath() {
    return identification.directoryPath;
}

std::string File::getExtension() {
    return identification.extension;
}

std::string File::getPath() {
    std::string path = getDirectoryPath() + "/" + getFileName();
    if(getExtension().length()>0) {
        path += "." + getExtension();
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



FileReader::FileReader(FileLocationDetails identification)
  : File(identification) {
    
    buffor = new char;
    bufforSize = 1;
    
    try {
        fileStream.open(getPath(), std::ios::in | std::ios::binary);
    }
    catch (const std::exception)
    {
        std::cout << "[ERROR] Trouble in opening file!";
    }
}
    
void FileReader::generateBuffor(unsigned int size)
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
    fileStream.close();
}
    
int FileReader::readLittleEndian()
{
    return getValueFromBuffor();
}

bool FileReader::readLittleEndianToBuffor()
{
    if(fileStream.read(buffor, bufforSize)) {
        return File::OK;
    }
    return File::ReadError;
}
 
int FileReader::getValueFromBuffor()
{
    return *((int *) buffor);
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
    
FileWriter::~FileWriter() {
    fileStream.close();
}
