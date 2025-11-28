#ifndef MAZE_API_H
#define MAZE_API_H

#include "maze.h"
#include "solver.h"

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

// Main entry point for Python → C
EXPORT int solve_maze_api(const char* maze_input, char* maze_output, int output_size);
EXPORT int generate_random_maze_api(char* out, int out_size);

#endif
