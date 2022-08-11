#ifndef PQUEUE_H_INCLUDED
#define PQUEUE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tree.h"
#include "file.h"


typedef struct _PriorityQueue{
    int size;
    int count;
    TreeNode *queue;
}_PriorityQueue;

typedef  _PriorityQueue *PriorityQueue;


PriorityQueue PriorityQueue_init(void);
PriorityQueue PriorityQueueDestroy(PriorityQueue);

// double the size every time
void PriorityQueueIncreaseSize(PriorityQueue);

int GetSize(PriorityQueue);
int GetCount(PriorityQueue);

bool IsPriorityQueueValid(PriorityQueue);
bool IsPriorityQueueFull(PriorityQueue);

void IncreaseCount(PriorityQueue);
void DecreaseCount(PriorityQueue);

void PriorityQueueInsertTreeNode(PriorityQueue, TreeNode);
TreeNode PriorityQueueGetTreeNode(PriorityQueue);





#endif // PQUEUE_H_INCLUDED
