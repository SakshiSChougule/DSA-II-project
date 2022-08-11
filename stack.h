
#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "file.h"
#include "tree.h"


typedef struct _Stack{
    int size;
    int count;
   node** trns;
}_Stack;

typedef _Stack *Stack;

Stack StackCreate(int size);
Stack StackDestroy(Stack);
Stack StackIncreaseSize(Stack);

bool IsStackValid(Stack);
bool IsStackFull(Stack);
bool IsStackEmpty(Stack);

void StackPush(Stack, TreeNode);
node* StackPop(Stack);
node* StackTop(Stack);

int GetStackCount(Stack);


#endif // STACK_H_INCLUDED
