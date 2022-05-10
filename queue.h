#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

typedef struct Queue{
    node **array;
    int size;
    int front,back;
}Queue;


#endif // QUEUE_H_INCLUDED
