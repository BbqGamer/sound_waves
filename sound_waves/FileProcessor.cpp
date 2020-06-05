#include "FileProcessor.h"

FileProcessor::FileProcessor(std::string Filename, States state)
{
    filename = Filename;
    if (state == Write)
    {
        file_stream.open(Filename, std::ios::out | std::ios::binary);
        m_state = Write;
    }
    else if (!ExistsCheck())
        std::cout << "File does not exist" << std::endl;
    else
    {
        file_stream.open(Filename, std::ios::in | std::ios::binary);
        m_state = Read;
    }
}

FileProcessor::~FileProcessor()
{
    closeFile();
}

bool FileProcessor::ExistsCheck()
{
    std::ifstream f(filename.c_str());
    return f.good();
}

void FileProcessor::closeFile()
{
    if (ExistsCheck())
        file_stream.close();
}

void FileProcessor::WriteShort(short value)
{
    if (m_state == Write)
        WriteWord(value);
    else
        std::cout << "File is not set to write!" << std::endl;
}

short FileProcessor::ReadShort()
{
    if (m_state == Read)
    {
        short value;
        ReadWord(value);
        value = (value >> 8) |
             (value << 8);
        return value;
    }
    else
        std::cout << "File is not set to read!" << std::endl;
    exit(0);
}
