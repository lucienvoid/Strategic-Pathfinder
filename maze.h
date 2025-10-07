#ifndef MAZE_H
#define MAZE_H

#define MAZE_SIZE 10
#define WALL '#'
#define PATH '.'
#define START 'S'
#define END 'E'
#define PLAYER 'P'
#define SOLUTION '*'

// Structure to represent a position in the maze
typedef struct {
    int row;
    int col;
} Position;

// Function declarations
void generate_maze(char maze[MAZE_SIZE][MAZE_SIZE]);
void print_maze(char maze[MAZE_SIZE][MAZE_SIZE]);
int is_valid_move(char maze[MAZE_SIZE][MAZE_SIZE], int row, int col);
Position find_start(char maze[MAZE_SIZE][MAZE_SIZE]);
Position find_end(char maze[MAZE_SIZE][MAZE_SIZE]);

#endif
