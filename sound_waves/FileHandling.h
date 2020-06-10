#pragma once

#include <string>
#include <fstream>
#include <iostream>

struct FileLocationDetails
{
    std::string fileName;
    std::string extension = "";
    std::string directoryPath = ".";
};


class File
{
    FileLocationDetails identification;
    
    File();
    
public:
    
    File(FileLocationDetails identification);
    
    bool checkIfExists();
    
    //return relative path from the root of a project
    //root is specified in project settings
    std::string getPath();
    
    friend std::ostream& operator<<(std::ostream& outs, File& fileToPrint);
};

std::ostream& operator<<(std::ostream& outs, File& fileToWrite);

class FileReader : public File
{
    std::ifstream fileStream;
    
    char * buffor = nullptr;
    unsigned char bufforSize = 0;
    
    void deleteBufforIfExists();
    
public:
    FileReader(FileLocationDetails identification);
    ~FileReader();
    
    void skipBytes(int numBytes);
    
    void alterBuffor(unsigned int size);
    
    int getValueFromBuffor();
    bool readLittleEndianToBuffor();
    int readLittleEndian();
    
    int readLittleEndianFromPositionInStream(size_t position);
    int readLittleEndianFromPositionInStream(size_t position, unsigned int size);
    
    void goToPositionInStream(size_t position);
    void closeIfOpen();
};


class FileWriter : public File
{
    std::ofstream fileStream;

public:
    
    FileWriter(FileLocationDetails identification);
    ~FileWriter();
    
    size_t getPositionInStream();
    void goToPositionInStream(size_t position);
    
    void closeIfOpen();
    
    void writeBigEndianString(std::string input);
    
    template <typename Word>
    void writeLittleEndian(Word value, unsigned size = sizeof(Word));
    
};


template <typename Word>
void FileWriter::writeLittleEndian(Word value, unsigned size) {
    for (; size; --size, value >>= 8) {
        fileStream.put(static_cast <char> (value & 0xFF));
    }
}
