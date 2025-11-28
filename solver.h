#ifndef SOLVER_H
#define SOLVER_H

#include "maze.h"
#include "queue.h"

// Expose directions[] for A*
extern int directions[4][2];

int solve_maze_bfs(char maze[MAZE_SIZE][MAZE_SIZE]);
void mark_solution_path(char maze[MAZE_SIZE][MAZE_SIZE],
                        int parent[MAZE_SIZE][MAZE_SIZE][2],
                        Position start, Position end);

#endif
