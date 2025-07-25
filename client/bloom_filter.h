#include <cstring>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "size_parameters.h"
#include "utils.h"

#define N_HASH 1                    //Equal to N_Threads
// #define MAX_BF_BIN_SIZE 1024
// #define N_BF_BITS 10

#define MAX_BF_BIN_SIZE 4194304
#define N_BF_BITS 22


int BloomFilter_Init(unsigned char** &BF);
int BloomFilter_Set(unsigned char** &BF, unsigned int* indices);
int BloomFilter_Set_N(unsigned char** &BF, unsigned int** indices, int n_idx);
int BloomFilter_Match(unsigned char** &BF, unsigned int* indices, bool* is_present);
int BloomFilter_Match_N(unsigned char** &BF, unsigned int** indices, unsigned int n_words, bool* is_present);
int BloomFilter_Clean(unsigned char** &BF);
int Trapdoor_Set(int** &T, int** r1, int i_offset, int j_offset);
int ZW_Set(int** &ZW, int** anew, int i_offset, int j_offset);

int BloomFilter_WriteBFtoFile(std::string bloomfilter_file, unsigned char** &BF);
int BloomFilter_ReadBFfromFile(std::string bloomfilter_file, unsigned char** &BF);
