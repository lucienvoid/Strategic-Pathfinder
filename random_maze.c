#include <stdlib.h>
#include <time.h>
#include "random_maze.h"
#include "maze.h"

// Fill maze with walls
static void fill_walls(char maze[MAZE_SIZE][MAZE_SIZE]) {
    for (int r = 0; r < MAZE_SIZE; r++)
        for (int c = 0; c < MAZE_SIZE; c++)
            maze[r][c] = WALL;
}

// Recursive division
static void divide(char maze[MAZE_SIZE][MAZE_SIZE], int row, int col, int height, int width) {
    if (height <= 2 || width <= 2)
        return;

    int horizontal = rand() % 2;

    if (horizontal) {
        int wall_row = row + (rand() % (height / 2)) * 2 + 1;

        for (int c = col; c < col + width; c++)
            maze[wall_row][c] = WALL;

        int passage = col + (rand() % (width / 2)) * 2;
        maze[wall_row][passage] = PATH;

        divide(maze, row, col, wall_row - row, width);
        divide(maze, wall_row + 1, col, (row + height) - (wall_row + 1), width);

    } else {
        int wall_col = col + (rand() % (width / 2)) * 2 + 1;

        for (int r = row; r < row + height; r++)
            maze[r][wall_col] = WALL;

        int passage = row + (rand() % (height / 2)) * 2;
        maze[passage][wall_col] = PATH;

        divide(maze, row, col, height, wall_col - col);
        divide(maze, row, wall_col + 1, height, (col + width) - (wall_col + 1));
    }
}

// Main generator
void generate_random_maze(char maze[MAZE_SIZE][MAZE_SIZE]) {
    srand(time(NULL));

    fill_walls(maze);

    for (int r = 1; r < MAZE_SIZE - 1; r++)
        for (int c = 1; c < MAZE_SIZE - 1; c++)
            maze[r][c] = PATH;

    divide(maze, 1, 1, MAZE_SIZE - 2, MAZE_SIZE - 2);

    maze[1][1] = START;
    maze[MAZE_SIZE - 2][MAZE_SIZE - 2] = END;
}
