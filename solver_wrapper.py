import ctypes
import os

# Load DLL from the same folder as this Python file
BASE_DIR = os.path.dirname(os.path.abspath(__file__))
DLL_PATH = os.path.join(BASE_DIR, "maze_solver.dll")

if not os.path.exists(DLL_PATH):
    raise FileNotFoundError(f"maze_solver.dll not found at: {DLL_PATH}")

lib = ctypes.CDLL(DLL_PATH)

lib.generate_random_maze_api.argtypes = [ctypes.c_char_p, ctypes.c_int]
lib.solve_bfs_api.argtypes = [ctypes.c_char_p, ctypes.c_char_p]
lib.solve_astar_api.argtypes = [ctypes.c_char_p, ctypes.c_char_p]

def generate_maze():
    buf = ctypes.create_string_buffer(1024)
    lib.generate_random_maze_api(buf, 1024)
    return buf.value.decode()

def solve_bfs(maze_str):
    inp = maze_str.encode()
    out = ctypes.create_string_buffer(2048)
    r = lib.solve_bfs_api(inp, out)
    if r != 0:
        raise Exception("BFS error")
    return out.value.decode()

def solve_astar(maze_str):
    inp = maze_str.encode()
    out = ctypes.create_string_buffer(2048)
    r = lib.solve_astar_api(inp, out)
    if r != 0:
        raise Exception("A* error")
    return out.value.decode()
