#include "solver.h"
#include "maze.h"
#include <stdio.h>

// Directions for BFS and A*
int directions[4][2] = {
    {-1, 0},  // up
    {1, 0},   // down
    {0, -1},  // left
    {0, 1}    // right
};

// ---------------------------------------------------------
// BFS MAZE SOLVER (Pure, DLL-safe, no printing)
// ---------------------------------------------------------

int solve_maze_bfs(char maze[MAZE_SIZE][MAZE_SIZE])
{
    Position start = find_start(maze);
    Position end   = find_end(maze);

    if (start.row == -1 || end.row == -1)
        return 0;

    int visited[MAZE_SIZE][MAZE_SIZE];
    int parent[MAZE_SIZE][MAZE_SIZE][2];

    // Initialize arrays
    for (int i = 0; i < MAZE_SIZE; i++) {
        for (int j = 0; j < MAZE_SIZE; j++) {
            visited[i][j] = 0;
            parent[i][j][0] = -1;
            parent[i][j][1] = -1;
        }
    }

    // Queue
    Queue q;
    init_queue(&q);

    enqueue(&q, start);
    visited[start.row][start.col] = 1;

    while (!is_queue_empty(&q)) {
        Position current = dequeue(&q);

        // Goal reached → backtrack path
        if (current.row == end.row && current.col == end.col) {
            mark_solution_path(maze, parent, start, end);
            free_queue(&q);
            return 1;
        }

        // Explore neighbors
        for (int d = 0; d < 4; d++) {
            int nr = current.row + directions[d][0];
            int nc = current.col + directions[d][1];

            if (is_valid_move(maze, nr, nc) && !visited[nr][nc]) {
                visited[nr][nc] = 1;

                parent[nr][nc][0] = current.row;
                parent[nr][nc][1] = current.col;

                Position next = {nr, nc};
                enqueue(&q, next);
            }
        }
    }

    free_queue(&q);
    return 0;   // No path found
}

// ---------------------------------------------------------
// MARK SOLUTION PATH
// ---------------------------------------------------------

void mark_solution_path(
        char maze[MAZE_SIZE][MAZE_SIZE],
        int parent[MAZE_SIZE][MAZE_SIZE][2],
        Position start,
        Position end)
{
    Position cur = end;

    while (!(cur.row == start.row && cur.col == start.col)) {

        // Only mark path cells (avoid overwriting S and E)
        if (maze[cur.row][cur.col] != START && maze[cur.row][cur.col] != END)
            maze[cur.row][cur.col] = SOLUTION;

        int pr = parent[cur.row][cur.col][0];
        int pc = parent[cur.row][cur.col][1];

        cur.row = pr;
        cur.col = pc;

        if (pr == -1 || pc == -1)
            break;  // safety guard
    }
}
