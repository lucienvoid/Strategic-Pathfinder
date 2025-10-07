#include <stdio.h>
#include <string.h>
#include "solver.h"

// Direction arrays for moving up, down, left, right
int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

// Solve the maze using Breadth-First Search algorithm
int solve_maze_bfs(char maze[MAZE_SIZE][MAZE_SIZE]) {
    // Find start and end positions
    Position start = find_start(maze);
    Position end = find_end(maze);

    if (start.row == -1 || end.row == -1) {
        printf("Start or end position not found!\n");
        return 0;
    }

    // Initialize visited array and parent array
    int visited[MAZE_SIZE][MAZE_SIZE];
    int parent[MAZE_SIZE][MAZE_SIZE][2];

    // Initialize all positions as not visited and no parent
    for (int i = 0; i < MAZE_SIZE; i++) {
        for (int j = 0; j < MAZE_SIZE; j++) {
            visited[i][j] = 0;
            parent[i][j][0] = -1;
            parent[i][j][1] = -1;
        }
    }

    // Create and initialize queue
    Queue q;
    init_queue(&q);

    // Start BFS from the starting position
    enqueue(&q, start);
    visited[start.row][start.col] = 1;

    printf("Starting BFS from position (%d, %d) to (%d, %d)\n", 
           start.row, start.col, end.row, end.col);

    // BFS main loop
    while (!is_queue_empty(&q)) {
        Position current = dequeue(&q);

        // Check if we reached the end
        if (current.row == end.row && current.col == end.col) {
            printf("Path found!\n");
            mark_solution_path(maze, parent, start, end);
            return 1;
        }

        // Explore all 4 directions
        for (int i = 0; i < 4; i++) {
            int new_row = current.row + directions[i][0];
            int new_col = current.col + directions[i][1];

            // Check if the new position is valid and not visited
            if (is_valid_move(maze, new_row, new_col) && !visited[new_row][new_col]) {
                Position new_pos = {new_row, new_col};

                visited[new_row][new_col] = 1;
                parent[new_row][new_col][0] = current.row;
                parent[new_row][new_col][1] = current.col;

                enqueue(&q, new_pos);
            }
        }
    }

    printf("No path found!\n");
    return 0;
}

// Mark the solution path in the maze
void mark_solution_path(char maze[MAZE_SIZE][MAZE_SIZE], 
                        int parent[MAZE_SIZE][MAZE_SIZE][2], 
                        Position start, Position end) {

    Position current = end;

    // Trace back from end to start using parent array
    while (current.row != start.row || current.col != start.col) {
        // Mark the path (but don't overwrite start and end)
        if (maze[current.row][current.col] != START && 
            maze[current.row][current.col] != END) {
            maze[current.row][current.col] = SOLUTION;
        }

        // Move to parent position
        int parent_row = parent[current.row][current.col][0];
        int parent_col = parent[current.row][current.col][1];

        current.row = parent_row;
        current.col = parent_col;
    }
}
