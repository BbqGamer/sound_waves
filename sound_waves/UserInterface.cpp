#include "UserInterface.h"
#include "Effect.h"

void startInterface() {
    std::cout << "Welcome to console interface of sound_waves" << std::endl << std::endl;
    std::cout << "Choose feature you want to try (number on keyboard): " << std::endl;
    showFeatures();
    int answer;
    std::cin >> answer;
    chooseFeature(answer);
}

void showFeatures() {
    std::cout << "1. Amplifier" << std::endl;
    std::cout << "2. Downsampler" << std::endl;
    std::cout << "3. Bit reduction" << std::endl;
    
    std::cout << "0. Exit program" << std::endl;
}

void chooseFeature(int answer) {
    switch (answer) {
        case 0:
            std::cout << "Exiting program" << std::endl;
            exit(0);
            break;
        case 1:
            startAmplifierFeature();
            break;
        case 2:
            startDownsamplerFeature();
            break;
        case 3:
            startBitReductionFeature();
            break;
        default:
            std::cout << "Invalid choice" << std::endl;
            startInterface();
            break;
    }
}

void startAmplifierFeature() {
    
    
    std::string sourceFileName;
    sourceFileName = askForSourceFileName();
    WavFileReader source(sourceFileName);
    
    std::string destinationFileName;
    destinationFileName = askForDestinationFileName();
    
    float multiplier;
    std::cout << "Value of sample value multiplication, if value is below 1 sound is attenuated" << std::endl;
    std::cin >> multiplier;
    
    Amplifier destination(source, destinationFileName, multiplier);
    destination.applyEffect();
    
    std::cout << "Amilifier ended it's job, returning to menu." << std::endl << std::endl;
    startInterface();
}

void startDownsamplerFeature() {
    std::string sourceFileName;
    sourceFileName = askForSourceFileName();
    WavFileReader source(sourceFileName);
    
    std::string destinationFileName;
    destinationFileName = askForDestinationFileName();
    
    short amount;
    std::cout << "Value of how much times you want to downsample: " << std::endl;
    std::cin >> amount;
    
    Downsampler destination(source, destinationFileName, amount);
    destination.applyEffect();
    
    std::cout << "DownSampler ended it's job, returning to menu." << std::endl << std::endl;
    startInterface();
    
}

void startBitReductionFeature() {
    std::string sourceFileName;
    sourceFileName = askForSourceFileName();
    WavFileReader source(sourceFileName);
    
    std::string destinationFileName;
    destinationFileName = askForDestinationFileName();
    
    int bitAmount;
    std::cout << "BitDepth value after conversion: " << std::endl;
    std::cin >> bitAmount;
    BitReductor destination(source, destinationFileName, bitAmount);
    destination.applyEffect();
    
    std::cout << "Bit Reductor ended it's job" << std::endl << std::endl;
    startInterface();
    
}

std::string askForSourceFileName() {
    std::string sourceFileName;
    std::cout << "Name of your file (no extension): ";
    std::cin >> sourceFileName;
    return sourceFileName;
}

std::string askForDestinationFileName() {
    std::string destinationFileName;
    std::cout << "Name of your destination file (these files end up in ./outputSamples): " << std::endl;
    std::cin >> destinationFileName;

    return destinationFileName;
}
