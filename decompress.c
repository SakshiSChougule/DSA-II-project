#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "tree.h"
#include "pqueue.h"
#include "freq.h"
#include "file.h"
#include "code.h"
#include "stack.h"
#include "decompress.h"


bool IsValidCompressedFile(char* filename);


char* CreateDecompressedFileName(char* filename){
    assert(filename != NULL);

    if (! IsValidCompressedFile(filename)){
        printf("Input file is not valid: should be *.comp\n");
        exit(EXIT_FAILURE);
    }


    // remove .comp suffix, add dehuff_ prefix
    long len = strlen(filename);

    char* filename_out = (char*) malloc((len - 5 + 7 + 1) *sizeof(char));
    assert(filename_out != NULL);


    strcpy(filename_out, "dehuff_");
    strncat(filename_out, filename, len - 5);

    return filename_out;
}


int ReadFileGetPadNumber(FILE* fp){
    assert(fp != NULL);
    fseek(fp, 0, SEEK_SET);
    return getc(fp);
}



int ReadFileGetCharCount(FILE* fp){
    assert(fp != NULL);
    fseek(fp, 1, SEEK_SET);
    return getc(fp);
}


Tree ReadHeaderProduceTree(FILE* fp, int char_count){
    assert(fp != NULL);
    fseek(fp, 2, SEEK_SET);     // start from the third char

    Stack s = StackCreate(char_count);

    int meet_char_count = 0;

    int buffer = getc(fp);
    int buffer_len = 8;
    int buffer_next = getc(fp);
    int this_bit, this_byte;

    TreeNode trn, trn1, trn2;

    while (! (meet_char_count == char_count && GetStackCount(s) == 1)){
        if (buffer_next == EOF){
            printf("EOF in header part. Wrong input file\n");
            exit(EXIT_FAILURE);
        }

        this_bit = GetOneBit(fp, &buffer, &buffer_len, &buffer_next);
        if (this_bit == 0){
            // internal node
            // post order traversal: left, right ,root
            trn = TreeNodeCreate(INTERNAL_NODE_C, 0);   //now that compression is already done, here occ does not matter
            // get two from the stack
            trn2 = StackPop(s);     // right child
            trn1 = StackPop(s);     // left child

            ConnectAsLeftChild(trn1, trn);
            ConnectAsRightChild(trn2, trn);

            StackPush(s, trn);
        }
        else{
            // this_bit == 1, a leaf node
            this_byte = GetOneByte(fp, &buffer, &buffer_len, &buffer_next);
            trn = TreeNodeCreate(this_byte, 0);
            StackPush(s, trn);

            //increase the meet_char_count
            meet_char_count += 1;
        }
    }

    
    fseek(fp, -1, SEEK_CUR);

    // now the tree is completed
    TreeNode root = StackPop(s);
    ResetInternalNodeToRootNode(root);
    Tree tr = TreeCreate(root);

    return tr;
}


void ReadFilePrintDecompression(FILE* fp_in, FILE* fp_out, Tree tr, int pad_num){
    assert(fp_in != NULL && fp_out != NULL);
    assert(tr != NULL && tr->root != NULL);
    assert(pad_num >= 0 && pad_num <= 7);

    int buffer = getc(fp_in);
    int buffer_len = 8;
    int buffer_next = getc(fp_in);
    int this_bit;

    TreeNode current = tr->root;

    while (buffer_next != EOF){
        this_bit = GetOneBit(fp_in, &buffer, &buffer_len, &buffer_next);
        if (this_bit == 0){
            current = current->left;
        }
        else{
            current = current->right;
        }

        if (IsLeafNode(current)){
            putc(GetC(current), fp_out);

            current = tr->root;
        }
    }

    // now buffer_next is EOF
    // reduce the buffer_len
    buffer_len -= pad_num;

    // and shift the byte, since the remaining bits start from left side
    buffer >>= pad_num;

    int mask;
    while (buffer_len > 0){
        mask = 1 << (buffer_len - 1);
        this_bit = mask & buffer;
        this_bit >>= (buffer_len - 1);
        this_bit &= 1;

        buffer_len -= 1;

        if (this_bit == 0){
            current = current->left;
        }
        else{
            current = current->right;
        }

        if (IsLeafNode(current)){
            putc(GetC(current), fp_out);

            current = tr->root;
        }
    }

    return;
}


bool IsValidCompressedFile(char* filename){
    assert(filename != NULL);

    long len = strlen(filename);
    return strcmp(".comp", filename + len - 5) == 0;
}





