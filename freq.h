#ifndef FREQ_H_INCLUDED
#define FREQ_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "file.h"


// read the file and count the frequency of each char
typedef struct _FreqTable{
    int size;
    int char_count;
    int *table;
}freq;

typedef freq *FreqTable;

freq* FreqTableCreate(int size);
freq* FreqTableDestroy(FreqTable);

void FreqTableInsert(FreqTable, int c);
int FreqTableGetCount(FreqTable, int c);


int FreqTableGetCharCount(FreqTable);

bool IsFreqTableValid(FreqTable);



#endif // FREQ_H_INCLUDED
