#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

// Generate a simple maze with predefined layout
void generate_maze(char maze[MAZE_SIZE][MAZE_SIZE]) {
    // Simple predefined maze layout for consistency
    char template_maze[MAZE_SIZE][MAZE_SIZE] = {
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', 'S', '.', '#', '.', '.', '.', '#', '.', '#'},
        {'#', '.', '.', '#', '.', '#', '.', '#', '.', '#'},
        {'#', '.', '#', '#', '.', '#', '.', '.', '.', '#'},
        {'#', '.', '.', '.', '.', '#', '#', '#', '.', '#'},
        {'#', '#', '#', '.', '.', '.', '.', '#', '.', '#'},
        {'#', '.', '.', '.', '#', '.', '.', '#', '.', '#'},
        {'#', '.', '#', '.', '#', '.', '.', '.', '.', '#'},
        {'#', '.', '#', '.', '.', '.', '#', '.', 'E', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
    };

    // Copy template to maze
    for (int i = 0; i < MAZE_SIZE; i++) {
        for (int j = 0; j < MAZE_SIZE; j++) {
            maze[i][j] = template_maze[i][j];
        }
    }
}

// Print the current state of the maze
void print_maze(char maze[MAZE_SIZE][MAZE_SIZE]) {
    printf("\n");
    for (int i = 0; i < MAZE_SIZE; i++) {
        for (int j = 0; j < MAZE_SIZE; j++) {
            printf("%c ", maze[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Check if a move to the given position is valid
int is_valid_move(char maze[MAZE_SIZE][MAZE_SIZE], int row, int col) {
    // Check boundaries
    if (row < 0 || row >= MAZE_SIZE || col < 0 || col >= MAZE_SIZE) {
        return 0;
    }

    // Check if it's not a wall
    if (maze[row][col] == WALL) {
        return 0;
    }

    return 1;
}

// Find the starting position in the maze
Position find_start(char maze[MAZE_SIZE][MAZE_SIZE]) {
    Position start = {-1, -1};

    for (int i = 0; i < MAZE_SIZE; i++) {
        for (int j = 0; j < MAZE_SIZE; j++) {
            if (maze[i][j] == START) {
                start.row = i;
                start.col = j;
                return start;
            }
        }
    }

    return start;
}

// Find the ending position in the maze
Position find_end(char maze[MAZE_SIZE][MAZE_SIZE]) {
    Position end = {-1, -1};

    for (int i = 0; i < MAZE_SIZE; i++) {
        for (int j = 0; j < MAZE_SIZE; j++) {
            if (maze[i][j] == END) {
                end.row = i;
                end.col = j;
                return end;
            }
        }
    }

    return end;
}
