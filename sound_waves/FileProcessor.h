#pragma once

#include <string>
#include <fstream>
#include <iostream>

class FileProcessor
{
    //this is used to operate on binary files
    
public:
    
    enum States
    {
        Read, Write
    };
    
    std::fstream file_stream;
    std::string filename;
    
    States m_state;
    
    //writes choosen word to file (little endian)
    template <typename Word>
    void WriteWord(Word value, unsigned size = sizeof(Word)); //writes choosen word to binary file
    
    //reads word from file
    template <class U>
    void ReadWord(U& variable);
    
    //check if a file with /filename/ exists
    bool ExistsCheck();
    
    //write to (0) or create a new file (1)
    FileProcessor(std::string Filename, States state = Write);
    //closes a file when destroyed
    ~FileProcessor();
    
    //Methods to write short (2 byte) values in little endian
    void WriteShort(short value);
    short ReadShort();

    void closeFile(); //closeFile
    
    friend std::ostream& operator<<(std::ostream& os, FileProcessor& obj);
};

template <typename Word>
void FileProcessor::WriteWord(Word value, unsigned size)
{
    for (; size; --size, value >>= 8)
    file_stream.put(static_cast <char> (value & 0xFF));
}

template <class U>
void FileProcessor::ReadWord(U& variable)
{
    file_stream.read((char*) &variable, sizeof(variable));
}

std::ostream& operator<<(std::ostream& os, FileProcessor& obj);
