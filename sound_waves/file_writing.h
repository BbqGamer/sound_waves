#ifndef file_writing_h
#define file_writing_h

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

ofstream create_wav_file(string filename, int num_hannels, int sample_rate, int bit_depth); //function to create file and add headers


void complete_wav_file(ofstream & f, size_t data_chunk_pos); //function that completes missing headers of a file


template <typename Word>
ostream& write_word(ostream& outs, Word value, unsigned size = sizeof(Word)); //writes choosen word to binary file


#endif
