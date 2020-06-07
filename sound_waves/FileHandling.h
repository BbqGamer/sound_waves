#pragma once

#include <string>
#include <fstream>
#include <iostream>

/*
 File contains classes to simplify using files written in Little Endian
 It provides one base File object, and two children FileReader and FileWriter
 
 FileReader contains method readLittleEndianToBuffor which is used to some number of bytes
 to a buffor. You can specify a size of a buffor with generate Buffor.
 (ReadLittleEndian() automatically, reads some bytes and returns value from buffor)
 
 FileWriter contains method writeLittleEndian which is used to write certain word to a file,
 size of a word depends on a size of variable type (can be also assigned explicitly).
 It supports integer values, BUT NOT FLOAT values.
 
 Both classes close their file streams on destruction.
 
 */

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
    
    enum fileCodes {
        OK,
        ReadError,
    };
    
    File(FileLocationDetails identification);
    
    bool checkIfExists();
    
    std::string getFileName();
    std::string getDirectoryPath();
    std::string getExtension();
    
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
    
    void generateBuffor(unsigned int size);
    void deleteBufforIfExists();
    
public:
    FileReader(FileLocationDetails identification);
    ~FileReader();
    
    int getValueFromBuffor();
    
    bool readLittleEndianToBuffor();
    int readLittleEndian();
};


class FileWriter : public File
{
    std::ofstream fileStream;

public:
    
    FileWriter(FileLocationDetails identification);
    ~FileWriter();
    
    template <typename Word>
    void writeLittleEndian(Word value, unsigned size = sizeof(Word));
    
};

template <typename Word>
void FileWriter::writeLittleEndian(Word value, unsigned size)
{
    for (; size; --size, value >>= 8)
    fileStream.put(static_cast <char> (value & 0xFF));
}
