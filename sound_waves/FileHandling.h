#pragma once

#include <string>
#include <fstream>
#include <iostream>

/*
 File contains classes to simplify using files written in Little Endian
 It provides one base File object, and two children FileReader and FileWriter
 
 FileReader contains method readLittleEndian which is used to some number of bytes
 to a buffer. (it depends on size of a buffer).
 
 
 
 Both classes close their file streams on destruction.
 
 */

class File
{
    
    std::string directoryPath;
    std::string fileName;
    std::string extension;

    File();
    
public:
    File(std::string fileName, std::string extension = "", std::string directoryPath = ".");
    
    bool checkIfExists();
    
    std::string getFileName();
    std::string getDirectoryPath();
    std::string getExtension();
    
    //return relative path from the root of a project
    //it might be necessary to change settings of IDE
    std::string getPath();
    
    friend std::ostream& operator<<(std::ostream& outs, File& fileToPrint);
    
};

std::ostream& operator<<(std::ostream& outs, File& fileToWrite);



class FileReader : public File
{
    std::ifstream fileStream;
    
public:
    FileReader(std::string fileName, std::string extension = "", std::string directoryPath = ".");
    ~FileReader();
    
    template <class Type>
    bool readLittleEndian(Type& buffor);
};

template <class Type>
bool FileReader::readLittleEndian(Type& buffor)
{
    if(fileStream.read((char*) &buffor, sizeof(buffor)))
        return 1;
    else
        return 0;
}



class FileWriter : public File
{
    
    std::ofstream fileStream;

public:
    
    FileWriter(std::string fileName, std::string extension = "", std::string directoryPath = ".");
    ~FileWriter();
    
    template <typename Word>
    void writeLittleEndian(Word value, unsigned size);
    
};

template <typename Word>
void FileWriter::writeLittleEndian(Word value, unsigned size)
{
    for (; size; --size, value >>= 8)
    fileStream.put(static_cast <char> (value & 0xFF));
}

