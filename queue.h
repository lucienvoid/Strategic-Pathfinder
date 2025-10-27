#ifndef QUEUE_H
#define QUEUE_H

#include "maze.h"

#define MAX_QUEUE_SIZE 200

// Simple queue structure for BFS
typedef struct {
    Position data[MAX_QUEUE_SIZE];
    int front;
    int rear;
    int size;
} Queue;

// Function declarations
void init_queue(Queue* q);
int is_queue_empty(Queue* q);
int is_queue_full(Queue* q);
void enqueue(Queue* q, Position pos);
Position dequeue(Queue* q);

#endif
