#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

Queue* init(int size){
    Queue *queue1 = (Queue*)malloc(sizeof(Queue));
    queue1->size = size;
    queue1->front = queue1->back = -1;
    queue1->array = (node**)malloc(sizeof(node*)*size);
    return queue1;
}

int isEmpty(Queue *queue){
  return queue->front == -1;
}

int isSizeOne(Queue *queue){
  return queue->front == queue->back && queue->front != -1;
}

void enQueue(Queue *queue,node *data){
  if (queue->back == queue->size - 1)
    return;
  queue->back = queue->back + 1;
  queue->array[queue->back] = data;
  if (queue->front == -1)
    queue->front = queue->front + 1;
}

node *deQueue(Queue *queue){
  if (isEmpty(queue))
    return NULL;
  node *temp_node = queue->array[queue->front];
  if (queue->front == queue->back) //only one item in queue
    queue->front = queue->back = -1;
  else
    queue->front = queue->front + 1;
  return temp_node;
}

node *getFront(Queue *queue){
  if (isEmpty(queue))
    return NULL;
  return queue->array[queue->front];
}
