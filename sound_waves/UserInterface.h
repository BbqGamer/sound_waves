#pragma once
#include <iostream>

void startInterface();

void showFeatures();
void chooseFeature(int answer);

void startAmplifierFeature();
void startDownsamplerFeature();
void startBitReductionFeature();

std::string askForSourceFileName();
std::string askForSourceDirectory();
std::string askForDestinationFileName();
