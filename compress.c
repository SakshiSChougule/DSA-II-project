#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "tree.h"
#include "pqueue.h"
#include "freq.h"
#include "file.h"
#include "code.h"



// add suffix to compressed file
char* CreateCompressedFileName(char* filename){
    assert(filename != NULL);

    char* filename_out = (char*) malloc((strlen(filename)+5) * sizeof(char));
    assert(filename_out != NULL);

    strcpy(filename_out, filename);
    strcat(filename_out, ".comp");

    return filename_out;
}



FreqTable ReadFileCountFrequency(FILE* fp){
    assert(fp != NULL);
    fseek(fp, 0, SEEK_SET);

    FreqTable fqtable = FreqTableCreate(ASCII_SIZE);

    // read file
    int c;

    while ((c = getc(fp)) != EOF){
        FreqTableInsert(fqtable, c);
    }

    return fqtable;
}


PriorityQueue UseFreqTableProducePriorityQueue(FreqTable fqtable){
    assert(fqtable != NULL && fqtable->table != NULL);
    assert(fqtable->size > 0);

    PriorityQueue pq = PriorityQueue_init();

    for (int i = 0; i < fqtable->size; i++){
        if (fqtable->table[i] > 0){
            // create a tree node and insert into the queue
            TreeNode trn = TreeNodeCreate(i, fqtable->table[i]);
            PriorityQueueInsertTreeNode(pq, trn);
        }
    }

    return pq;
}


Tree UsePriorityQueueProduceTree(PriorityQueue pq){
    assert(IsPriorityQueueValid(pq));

    // pick two trn nodes from the queue
    // combine them, smaller occ be the right child
    // and insert back to the queue
    // until only one trn left
    TreeNode trn1, trn2, trn_parent;
    int trn_parent_occ;

    while (GetCount(pq) != 1){
        trn1 = PriorityQueueGetTreeNode(pq);
        trn2 = PriorityQueueGetTreeNode(pq);

        trn_parent_occ = SumTwoOcc(trn1, trn2);
        trn_parent = TreeNodeCreate(INTERNAL_NODE_C, trn_parent_occ);

        ConnectAsLeftChild(trn2, trn_parent);
        ConnectAsRightChild(trn1, trn_parent);

        PriorityQueueInsertTreeNode(pq, trn_parent);
    }

    TreeNode root = PriorityQueueGetTreeNode(pq);
    ResetInternalNodeToRootNode(root);

    Tree tr = TreeCreate(root);
    return tr;
}


void UseTreeProduceCodeWordFunction(CodeWord cw, TreeNode trn){
    if (trn != NULL){
        if (IsLeafNode(trn)){
            CodeWordNode cwn = CodeWordNodeCreate(trn);
            CodeWordInsertNode(cw, cwn);
        }
        else{
            UseTreeProduceCodeWordFunction(cw, trn->left);
            UseTreeProduceCodeWordFunction(cw, trn->right);
        }
    }

    return;
}


CodeWord UseTreeProduceCodeWord(Tree tr){
    assert(tr != NULL);

    CodeWord cw = CodeWordCreate(ASCII_SIZE);

    UseTreeProduceCodeWordFunction(cw, tr->root);

    return cw;
}




int ReadFilePrintCompression(FILE* fp_in, FILE* fp_out, CodeWord cw){
    assert(fp_in != NULL && fp_out != NULL);
    assert(cw != NULL);
    assert(cw->size > 0 && cw->list != NULL);

    // move the file descriptor to the start of the file
    // read again
    fseek(fp_in, 0, SEEK_SET);

    int c;
    int buffer = 0;
    int buffer_len = 0;

    CodeWordNode cwn;

    while ((c = getc(fp_in)) != EOF){
        cwn = CodeWordGetNode(cw, c);
        PrintCodeWordToFile(fp_out, &buffer, &buffer_len, cwn);
    }

    // after finishing , pad the last byte if necessary
    int pad_num = PadByte(fp_out, &buffer, &buffer_len);
    return pad_num;
}


void PrintCompressionTreeFunction(FILE* fp, int* buffer_p, int* buffer_len_p, TreeNode trn){
    assert(fp != NULL);
    assert(buffer_p != NULL && buffer_len_p != NULL);

    if (trn != NULL){
        // post order traversal: left, right, root
        // check this node first
        if (IsLeafNode(trn)){
            // for leaf node: print 1 + byte to show that it is a leaf node and contains a valid character
            PrintOneBit(fp, buffer_p, buffer_len_p, 1);
            PrintOneByte(fp, buffer_p, buffer_len_p, GetC(trn));
        }
        else{
            // internal node
            // go down left and right first
            PrintCompressionTreeFunction(fp, buffer_p, buffer_len_p, trn->left);
            PrintCompressionTreeFunction(fp, buffer_p, buffer_len_p, trn->right);

            // then print the bit 0
            PrintOneBit(fp, buffer_p, buffer_len_p, 0);
        }
    }

    return;
}





void PrintCompressionTree(FILE* fp, Tree tr){
    assert(fp != NULL);
    assert(tr != NULL && tr->root != NULL);

    // output post order traversal of the tree
    // during decompression, use stack to rebuild the tree
    int buffer = 0;
    int buffer_len = 0;
    PrintCompressionTreeFunction(fp, &buffer, &buffer_len, tr->root);
    PadByte(fp, &buffer, &buffer_len);

    return;
}



void PrintFirstByteEmpty(FILE* fp){
    assert(fp != NULL);
    fseek(fp, 0, SEEK_SET);
    putc(0, fp);
    return;
}


void RePrintFirstByteWithPadNumber(FILE* fp, int pad_num){
    assert(fp != NULL);
    assert(pad_num >= 0 && pad_num <= 7);

    fseek(fp, 0, SEEK_SET);
    putc(pad_num, fp);
    return;
}


void PrintSecondByteCharCount(FILE* fp, FreqTable fqtable){
    assert(fp != NULL);
    assert(IsFreqTableValid(fqtable));

    fseek(fp, 1, SEEK_SET);

    int char_count = FreqTableGetCharCount(fqtable);

    
    putc(char_count , fp);

    return;
}



