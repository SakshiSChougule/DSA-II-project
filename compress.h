#ifndef COMPRESS_H_INCLUDED
#define COMPRESS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tree.h"
#include "pqueue.h"
#include "freq.h"
#include "file.h"
#include "code.h"


// first byte = number of bits pad
// second byte = number of symbols used  so that the stack can rebuild the tree
// then tree
// then the main body


char* CreateCompressedFileName(char* filename);
FreqTable ReadFileCountFrequency(FILE* fp);

PriorityQueue UseFreqTableProducePriorityQueue(FreqTable);

Tree UsePriorityQueueProduceTree(PriorityQueue);
void UseTreeProduceCodeWordFunction(CodeWord cw, TreeNode trn);
CodeWord UseTreeProduceCodeWord(Tree tr);
void PrintCompressionTreeFunction(FILE* fp, int* buffer_p, int* buffer_len_p, TreeNode trn);

void PrintCompressionTree(FILE* fp, Tree tr);

int ReadFilePrintCompression(FILE* fp_in, FILE* fp_out, CodeWord cw);

void PrintFirstByteEmpty(FILE* fp);
void RePrintFirstByteWithPadNumber(FILE* fp, int pad_num);

void PrintSecondByteCharCount(FILE* fp, FreqTable);




#endif // COMPRESS_H_INCLUDED
