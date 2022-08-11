#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "code.h"

#define ASCII_SIZE 256
#define SIZE_FACTOR 2

const int power_of_2[9];

void PrintByteInBits(int c, int len);

FILE* OpenFileWithMode(char* filename, char* mode);
FILE* CloseFile(FILE* fp);

int GetOneBit(FILE* fp, int* buffer_p, int* unread_num_p, int* buffer_next_p);
int GetOneByte(FILE* fp, int* buffer_p, int* unread_num_p, int* buffer_next_p);

void PrintOneBit(FILE* fp, int* buffer_p, int* buffer_len_p, int this_bit);
void PrintOneByte(FILE* fp, int* buffer_p, int* buffer_len_p, int this_byte);

int PadByte(FILE* fp, int* buffer_p, int* buffer_len_p);




#endif // FILE_H_INCLUDED
