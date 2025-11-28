#ifndef ASTAR_H
#define ASTAR_H

#include "maze.h"

typedef struct {
    Position pos;
    int f_cost;
} Node;

typedef struct {
    Node* data;
    int size;
    int capacity;
} MinHeap;

void init_heap(MinHeap* h);
void resize_heap(MinHeap* h);
void heapify_up(MinHeap* h, int idx);
void heapify_down(MinHeap* h, int idx);
void heap_push(MinHeap* h, Node n);
Node heap_pop(MinHeap* h);
int heap_empty(MinHeap* h);

int solve_maze_astar(char maze[MAZE_SIZE][MAZE_SIZE]);

#endif
