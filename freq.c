#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "freq.h"
#include "file.h"

freq* FreqTableCreate(int size){
    assert(size > 0);

    freq* fqtable = (freq*) malloc(sizeof(freq));
    assert(fqtable != NULL);

    fqtable->size = size;
    fqtable->char_count = 0;

    fqtable->table = (int*) malloc(size * sizeof(int));
    assert(fqtable->table != NULL);

    for (int i = 0; i < size; i++){
        fqtable->table[i] = 0;
    }

    return fqtable;
}


freq* FreqTableDestroy(FreqTable fqtable){
    assert(IsFreqTableValid(fqtable));

    free(fqtable->table);
    fqtable->table = NULL;

    free(fqtable);
    fqtable = NULL;

    return fqtable;
}


bool IsFreqTableValid(FreqTable fqtable){
    return fqtable != NULL && fqtable->size > 0 && fqtable->char_count >= 0 && fqtable->table != NULL;
}


void FreqTableInsert(FreqTable fqtable, int c){
    assert(IsFreqTableValid(fqtable));
    assert(c >= 0 && c < fqtable->size);
    assert(fqtable->table[c] >= 0);

    if (fqtable->table[c] == 0){
        fqtable->char_count += 1;
    }

    fqtable->table[c] += 1;
    
    return;
}


int FreqTableGetCount(FreqTable fqtable, int c){
    assert(IsFreqTableValid(fqtable));
    assert(c >= 0 && c < fqtable->size);
    assert(fqtable->table[c] >= 0);

    return fqtable->table[c];
}




int FreqTableGetCharCount(FreqTable fqtable){
    assert(IsFreqTableValid(fqtable));
    return fqtable->char_count;
}


