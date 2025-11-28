#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

void init_queue(Queue* q) {
    q->capacity = 32;  
    q->data = (Position*)malloc(sizeof(Position) * q->capacity);
    q->front = 0;
    q->rear = 0;
    q->size = 0;
}

static void resize_queue(Queue* q) {
    q->capacity *= 2;
    q->data = (Position*)realloc(q->data, sizeof(Position) * q->capacity);
}

void enqueue(Queue* q, Position p) {
    if (q->size == q->capacity)
        resize_queue(q);

    q->data[q->rear] = p;
    q->rear = (q->rear + 1) % q->capacity;
    q->size++;
}

Position dequeue(Queue* q) {
    Position p = q->data[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->size--;
    return p;
}

int is_queue_empty(Queue* q) {
    return q->size == 0;
}

void free_queue(Queue* q) {
    free(q->data);
}
