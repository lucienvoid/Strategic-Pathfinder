#ifndef MAZE_H
#define MAZE_H

#define MAZE_SIZE 10
#define WALL '#'
#define PATH '.'
#define START 'S'
#define END 'E'
#define PLAYER 'P'
#define SOLUTION '*'

typedef struct {
    int row;
    int col;
} Position;

// Parsing + Serialization (NEW, required for DLL)
int parseMazeFromString(char maze[MAZE_SIZE][MAZE_SIZE], const char* input);
int serializeMazeToString(char maze[MAZE_SIZE][MAZE_SIZE], char* out);

// Validation + helpers
void print_maze(char maze[MAZE_SIZE][MAZE_SIZE]);
int is_valid_move(char maze[MAZE_SIZE][MAZE_SIZE], int row, int col);
Position find_start(char maze[MAZE_SIZE][MAZE_SIZE]);
Position find_end(char maze[MAZE_SIZE][MAZE_SIZE]);

#endif
