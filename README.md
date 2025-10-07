# Strategic Pathfinding in Discrete Spaces

## Compilation Instructions

To compile the project, use:
```bash
gcc main.c maze.c queue.c solver.c -o maze_solver
```

## Running the Program

After compilation, run:
```bash
./maze_solver
```

## File Structure

- main.c - Main program with menu system
- maze.h/maze.c - Maze generation and utility functions
- queue.h/queue.c - Simple queue implementation for BFS
- solver.h/solver.c - BFS pathfinding algorithm

## Features

1. **Manual Mode**: Navigate the maze using WASD keys
2. **Automatic Mode**: Let BFS algorithm solve the maze
3. **Simple 10x10 maze with clear path visualization**

## Legend

- `#` = Wall
- `.` = Path
- `S` = Start position
- `E` = End position
- `P` = Player position (manual mode)
- `*` = Solution path (automatic mode)
