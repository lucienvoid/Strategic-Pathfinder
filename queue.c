#include <stdio.h>
#include "queue.h"

// Initialize the queue
void init_queue(Queue* q) {
    q->front = 0;
    q->rear = -1;
    q->size = 0;
}

// Check if the queue is empty
int is_queue_empty(Queue* q) {
    return q->size == 0;
}

// Check if the queue is full
int is_queue_full(Queue* q) {
    return q->size == MAX_QUEUE_SIZE;
}

// Add an element to the rear of the queue
void enqueue(Queue* q, Position pos) {
    if (is_queue_full(q)) {
        printf("Queue is full! Cannot enqueue.\n");
        return;
    }

    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = pos;
    q->size++;
}

// Remove and return the front element of the queue
Position dequeue(Queue* q) {
    Position empty_pos = {-1, -1};

    if (is_queue_empty(q)) {
        printf("Queue is empty! Cannot dequeue.\n");
        return empty_pos;
    }

    Position result = q->data[q->front];
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    q->size--;

    return result;
}
