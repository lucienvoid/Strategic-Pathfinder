# Maze Solver Visualization (BFS, A*, Streamlit + C Backend)

This project implements a complete maze-solving system using a C backend and a Streamlit-based Python frontend.  
It supports two pathfinding algorithms (BFS and A*) and includes real-time visualization, performance metrics, and random maze generation.

The project was developed as part of the Data Structures Phase-3 PBL.

---

## Features

### Algorithms
- Breadth-First Search (BFS)
- A* Search with Manhattan heuristic
- Clean DLL-based integration between Python and C

### Visualization
- Step-by-step animated traversal  
- Frontiers, visited cells, and final path rendering  
- Adjustable animation speed  
- Side-by-side BFS vs A* comparison mode  
- Color-coded visualization grid  
- Heatmap based on BFS distance mapping  

### Maze Generation
- Random maze generation using Recursive Division method  
- Custom maze input  
- Preserves start and end positions  

### Optimization
- Dynamic queue implementation in C  
- Heap-based priority queue for A*  
- Reduced memory footprint  
- Efficient grid serialization for DLL boundary  

---

## Project Structure

MazeSolver/
│
├── maze.c
├── maze.h
├── solver.c
├── solver.h
├── astar.c
├── astar.h
├── random_maze.c
├── random_maze.h
├── queue.c
├── queue.h
│
├── maze_api.c
├── maze_api.h
├── maze_solver.dll # compiled shared library
│
├── solver_wrapper.py # Python-to-C bridge via ctypes
├── visualizer.py # animation and rendering engine
├── maze_utils.py # parsing and formatting helpers
└── streamlit_app.py # main UI


---

## Build Instructions (Windows)

### Requirements
- GCC (MinGW or similar)
- Python 3.11+
- Streamlit

### 1. Compile the C backend into a DLL

Run inside the project directory:

gcc -shared -o maze_solver.dll maze_api.c maze.c solver.c astar.c random_maze.c queue.c -I.


This generates `maze_solver.dll`, which is used directly by Python.

---

## Python Environment Setup

python -m venv venv
venv\Scripts\activate
pip install streamlit


No additional dependencies are required.

---

## Running the Application

Start the Streamlit UI:

streamlit run app.py


The application will open in your browser.  
You can:
 
- Generate a random maze  
- Choose BFS, A* or manual solving modes  
- Visualize step-by-step traversal  
- Compare algorithms side-by-side  

---

## Maze Format

The solver expects a 10×10 character grid using:

= Wall

. = Path
S = Start
E = End

= Solution (output)

Example:
##########
#S....#..#
#.#..##..#
#.#......#
#...###..#
###....#.#
#....#..##
#.#..#...#
#.#....#E#
##########


---

## Internal Architecture Overview

### C Backend
- BFS implemented using a dynamically growing queue
- A* implemented using a binary min-heap
- Random maze generated using recursive division
- Serialization and deserialization layer to pass grids across the DLL boundary
- Path reconstruction handled inside C for maximum performance

### Python Frontend
- ctypes wrapper for calling C functions
- Custom visualization engine:
  - Frontier marking
  - Visited node highlighting
  - Animated path reconstruction
  - Adjustable speed slider
- Heatmap rendering using BFS distances
- Streamlit UI for interactive controls

---

## Performance

Even with Python visualization, algorithm solving is executed in C:

- BFS runs in O(V + E)
- A* runs with improved pruning using Manhattan heuristic
- Visualization operates on cached frames for smooth playback
- Memory dynamically allocated and expanded in C structures

---

## Usage Notes

- The visualization system operates independently of the backend solver.
- The C backend always provides the correct final solved maze.
- The Python visualizer provides a detailed explanation of how the algorithm behaves internally.

---

## License

This project is released for academic and learning purposes.  
All components are free to use and modify.

