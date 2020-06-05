#include "FileHandling.h"

File::File(std::string fileName, std::string extension, std::string directoryPath)
    : fileName{fileName}, extension{extension}, directoryPath{directoryPath} {}

bool File::checkIfExists() {
    std::ifstream f(getPath().c_str());
    return f.good();
}

std::string File::getFileName() {
    return fileName;
}

std::string File::getDirectoryPath() {
    return directoryPath;
}

std::string File::getExtension() {
    return extension;
}

std::string File::getPath() {
    std::string path = directoryPath + "/" + fileName;
    if(extension.length()>0) {
        path += "." + extension;
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



FileReader::FileReader(std::string fileName, std::string extension, std::string directoryPath)
  : File(fileName, extension, directoryPath) {
    try {
        fileStream.open(getPath(), std::ios::in | std::ios::binary);
    }
    catch (const std::exception)
    {
        std::cout << "[ERROR] Trouble in opening file!";
    }
}
    
FileReader::~FileReader() {
    fileStream.close();
}



FileWriter::FileWriter(std::string fileName, std::string extension, std::string directoryPath)
    : File(fileName, extension, directoryPath) {
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
