#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "maze.h"

// ---------------------
// PARSE STRING → MAZE[]
// ---------------------
int parseMazeFromString(char maze[MAZE_SIZE][MAZE_SIZE], const char* input) 
{
    int row = 0, col = 0;

    for (int i = 0; input[i] != '\0' && row < MAZE_SIZE; i++) {
        char c = input[i];

        if (c == '\n') {
            if (col != MAZE_SIZE) return 0;   // invalid line length
            row++;
            col = 0;
        } else {
            if (col >= MAZE_SIZE) return 0;   // too long line
            maze[row][col++] = c;
        }
    }

    return (row == MAZE_SIZE - 1) ? 1 : 0;
}

// -------------------------
// SERIALIZE MAZE → STRING
// -------------------------
int serializeMazeToString(char maze[MAZE_SIZE][MAZE_SIZE], char* out)
{
    int k = 0;

    for (int i = 0; i < MAZE_SIZE; i++) {
        for (int j = 0; j < MAZE_SIZE; j++) {
            out[k++] = maze[i][j];
        }
        out[k++] = '\n';
    }

    out[k] = '\0';
    return 1;
}

// -------------------------
// PRINT (DEBUG ONLY)
// -------------------------
void print_maze(char maze[MAZE_SIZE][MAZE_SIZE])
{
    for (int i = 0; i < MAZE_SIZE; i++) {
        for (int j = 0; j < MAZE_SIZE; j++) {
            printf("%c ", maze[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// -------------------------
// VALID MOVE?
// -------------------------
int is_valid_move(char maze[MAZE_SIZE][MAZE_SIZE], int row, int col)
{
    if (row < 0 || row >= MAZE_SIZE || col < 0 || col >= MAZE_SIZE)
        return 0;

    if (maze[row][col] == WALL)
        return 0;

    return 1;
}

// -------------------------
// FIND START
// -------------------------
Position find_start(char maze[MAZE_SIZE][MAZE_SIZE])
{
    Position pos = {-1, -1};

    for (int i = 0; i < MAZE_SIZE; i++)
        for (int j = 0; j < MAZE_SIZE; j++)
            if (maze[i][j] == START) {
                pos.row = i;
                pos.col = j;
                return pos;
            }

    return pos;
}

// -------------------------
// FIND END
// -------------------------
Position find_end(char maze[MAZE_SIZE][MAZE_SIZE])
{
    Position pos = {-1, -1};

    for (int i = 0; i < MAZE_SIZE; i++)
        for (int j = 0; j < MAZE_SIZE; j++)
            if (maze[i][j] == END) {
                pos.row = i;
                pos.col = j;
                return pos;
            }

    return pos;
}
