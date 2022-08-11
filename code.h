#ifndef CODE_H_INCLUDED
#define CODE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tree.h"
#include "pqueue.h"
#include "freq.h"
#include "file.h"


typedef struct _CodeWordNode{
    int c;
    int bit_num;        // total number of bits
    int byte_num;        // total number of bytes
    int *s;
}code;

typedef code *CodeWordNode;

struct _CodeWord{
    int size;
    code** list;
};

typedef struct _CodeWord *CodeWord;


code* CodeWordNodeCreate(node* t);
code* CodeWordNodeDestroy(code* c);


CodeWord CodeWordCreate(int size);
CodeWord CodeWordDestroy(CodeWord);

void CodeWordInsertNode(CodeWord, CodeWordNode);

CodeWordNode CodeWordGetNode(CodeWord, int c);

void PrintCodeWordToFile(FILE* fp, int* buffer_p, int* buffer_len_p, CodeWordNode cwn);

bool IsCodeWordNodeValid(CodeWordNode cwn);




#endif // CODE_H_INCLUDED
