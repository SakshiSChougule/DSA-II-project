#ifndef DECOMPRESS_H_INCLUDED
#define DECOMPRESS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tree.h"
#include "pqueue.h"
#include "freq.h"
#include "file.h"
#include "code.h"
#include "stack.h"

// remove .comp suffix, add dehuff_ prefix
char* CreateDecompressedFileName(char* filename);

void decompression_status(char* name_in, char* name_out, FILE* fp_in, FILE* fp_out);

int ReadFileGetPadNumber(FILE* fp);
int ReadFileGetCharCount(FILE* fp);

Tree ReadHeaderProduceTree(FILE* fp, int char_count);

void ReadFilePrintDecompression(FILE* fp_in, FILE* fp_out, Tree tr, int pad_num);

int ReadFirstByteGetPadNumber(FILE* fp);



#endif // DECOMPRESS_H_INCLUDED
