#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

#include <stdlib.h>
#include <limits.h>
#include <math.h>

#include "astar.h"
#include "solver.h"
#include "maze.h"

// -------------------------
// MIN HEAP IMPLEMENTATION
// -------------------------

static void swap(Node* a, Node* b) {
    Node t = *a;
    *a = *b;
    *b = t;
}

void init_heap(MinHeap* h) {
    h->capacity = 64;
    h->size = 0;
    h->data = (Node*)malloc(sizeof(Node) * h->capacity);
}

void resize_heap(MinHeap* h) {
    h->capacity *= 2;
    h->data = (Node*)realloc(h->data, sizeof(Node) * h->capacity);
}

void heapify_up(MinHeap* h, int idx) {
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (h->data[idx].f_cost >= h->data[parent].f_cost)
            break;

        swap(&h->data[idx], &h->data[parent]);
        idx = parent;
    }
}

void heapify_down(MinHeap* h, int idx) {
    int smallest = idx;

    while (1) {
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;

        if (left < h->size && h->data[left].f_cost < h->data[smallest].f_cost)
            smallest = left;

        if (right < h->size && h->data[right].f_cost < h->data[smallest].f_cost)
            smallest = right;

        if (smallest == idx)
            break;

        swap(&h->data[idx], &h->data[smallest]);
        idx = smallest;
    }
}

void heap_push(MinHeap* h, Node n) {
    if (h->size == h->capacity)
        resize_heap(h);

    h->data[h->size] = n;
    heapify_up(h, h->size);
    h->size++;
}

Node heap_pop(MinHeap* h) {
    Node top = h->data[0];
    h->size--;
    h->data[0] = h->data[h->size];
    heapify_down(h, 0);
    return top;
}

int heap_empty(MinHeap* h) {
    return h->size == 0;
}

// -------------------------
// A* HEURISTIC
// -------------------------

static int heuristic(Position a, Position b) {
    return abs(a.row - b.row) + abs(a.col - b.col); // Manhattan distance
}

// -------------------------
// A* MAIN ALGORITHM
// -------------------------

int solve_maze_astar(char maze[MAZE_SIZE][MAZE_SIZE])
{
    Position start = find_start(maze);
    Position end   = find_end(maze);

    if (start.row == -1 || end.row == -1)
        return 0;

    int g_cost[MAZE_SIZE][MAZE_SIZE];
    int f_cost[MAZE_SIZE][MAZE_SIZE];
    int parent[MAZE_SIZE][MAZE_SIZE][2];

    // Initialize
    for (int r = 0; r < MAZE_SIZE; r++) {
        for (int c = 0; c < MAZE_SIZE; c++) {
            g_cost[r][c] = INT_MAX;
            f_cost[r][c] = INT_MAX;
            parent[r][c][0] = -1;
            parent[r][c][1] = -1;
        }
    }

    g_cost[start.row][start.col] = 0;
    f_cost[start.row][start.col] = heuristic(start, end);

    MinHeap heap;
    init_heap(&heap);

    Node s = {start, f_cost[start.row][start.col]};
    heap_push(&heap, s);

    while (!heap_empty(&heap)) {
        Node current = heap_pop(&heap);
        Position p = current.pos;

        if (p.row == end.row && p.col == end.col) {
            mark_solution_path(maze, parent, start, end);
            free(heap.data);
            return 1;
        }

        for (int d = 0; d < 4; d++) {
            int nr = p.row + directions[d][0];
            int nc = p.col + directions[d][1];

            if (!is_valid_move(maze, nr, nc))
                continue;

            int tentative = g_cost[p.row][p.col] + 1;

            if (tentative < g_cost[nr][nc]) {
                g_cost[nr][nc] = tentative;
                f_cost[nr][nc] = tentative + heuristic((Position){nr,nc}, end);

                parent[nr][nc][0] = p.row;
                parent[nr][nc][1] = p.col;

                Node next = { {nr,nc}, f_cost[nr][nc] };
                heap_push(&heap, next);
            }
        }
    }

    free(heap.data);
    return 0;
}
