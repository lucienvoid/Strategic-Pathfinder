#ifndef QUEUE_H
#define QUEUE_H

#include "maze.h"

typedef struct {
    Position* data;   // dynamic array of positions
    int front;
    int rear;
    int size;
    int capacity;
} Queue;

void init_queue(Queue* q);
void enqueue(Queue* q, Position p);
Position dequeue(Queue* q);
int is_queue_empty(Queue* q);
void free_queue(Queue* q);

#endif
