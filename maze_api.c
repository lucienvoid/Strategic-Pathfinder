#include <string.h>
#include <stdio.h>

#include "maze.h"
#include "solver.h"
#include "astar.h"
#include "random_maze.h"

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

#ifdef __cplusplus
extern "C" {
#endif

void maze_to_buf(char maze[MAZE_SIZE][MAZE_SIZE], char* out) {
    int pos = 0;
    for (int i=0;i<MAZE_SIZE;i++) {
        for(int j=0;j<MAZE_SIZE;j++){
            out[pos++] = maze[i][j];
        }
        out[pos++] = '\n';
    }
    out[pos] = '\0';
}

EXPORT int generate_random_maze_api(char* out, int out_size) {
    char m[MAZE_SIZE][MAZE_SIZE];
    generate_random_maze(m);

    char temp[200];
    maze_to_buf(m, temp);

    if (strlen(temp)+1 > out_size) return -1;

    strcpy(out, temp);
    return 0;
}

EXPORT int solve_bfs_api(char* in_maze, char* out_maze) {
    char m[MAZE_SIZE][MAZE_SIZE];

    int r = 0, c = 0;
    for (int i = 0; i < strlen(in_maze); i++) {
        if (in_maze[i] == '\n') { r++; c = 0; continue; }
        m[r][c++] = in_maze[i];
    }

    if (!solve_maze_bfs(m))
        return -2;

    char temp[200];
    maze_to_buf(m, temp);
    strcpy(out_maze, temp);

    return 0;
}

EXPORT int solve_astar_api(char* in_maze, char* out_maze) {
    char m[MAZE_SIZE][MAZE_SIZE];

    int r = 0, c = 0;
    for (int i = 0; i < strlen(in_maze); i++) {
        if (in_maze[i] == '\n') { r++; c = 0; continue; }
        m[r][c++] = in_maze[i];
    }

    if (!solve_maze_astar(m))
        return -2;

    char temp[200];
    maze_to_buf(m, temp);
    strcpy(out_maze, temp);

    return 0;
}

#ifdef __cplusplus
}
#endif
