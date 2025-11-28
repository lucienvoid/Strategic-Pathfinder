import streamlit as st
import time
import threading
from http.server import BaseHTTPRequestHandler, HTTPServer
import urllib.parse

from solver_wrapper import (
    generate_maze,
    solve_bfs,
    solve_astar
)

from visualizer import (
    render_color_grid,
    parse_maze_string
)

# ============================================================
# PAGE CONFIG
# ============================================================
st.set_page_config(page_title="Maze Solver - WASD Mode", layout="centered")

# ============================================================
# WASD MICROSERVER (RECEIVES KEYS FROM wasd.html)
# ============================================================

if "wasd_key" not in st.session_state:
    st.session_state.wasd_key = None

class WASDHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        parsed = urllib.parse.urlparse(self.path)
        params = urllib.parse.parse_qs(parsed.query)
        key = params.get("key", [None])[0]

        if key:
            st.session_state.wasd_key = key

        self.send_response(200)
        self.end_headers()
        self.wfile.write(b"OK")

def run_server():
    server = HTTPServer(("127.0.0.1", 5678), WASDHandler)
    server.serve_forever()

if "server_started" not in st.session_state:
    threading.Thread(target=run_server, daemon=True).start()
    st.session_state.server_started = True

# ============================================================
# SIDEBAR + INIT
# ============================================================

if "maze" not in st.session_state:
    st.session_state.maze = generate_maze()

maze = st.session_state.maze

st.sidebar.title("Maze Controls")

mode = st.sidebar.radio(
    "Mode",
    [
        "Solve Instantly",
        "Visualize Step-by-Step",
        "Manual Solving (WASD)",
        "Algorithm Comparison",
        "Manual vs BFS vs A*",
    ]
)

if st.sidebar.button("Generate New Random Maze"):
    st.session_state.maze = generate_maze()
    st.session_state.manual_grid = None
    st.session_state.player_pos = None
    st.session_state.steps = 0
    st.rerun()

if st.sidebar.button("Reset Maze"):
    for k in list(st.session_state.keys()):
        del st.session_state[k]
    st.rerun()

# ============================================================
# HEADER
# ============================================================

st.header("Maze Solver (C Backend + WASD External Control)")

parsed_maze = parse_maze_string(maze)
st.markdown("### Current Maze")
st.markdown(render_color_grid(parsed_maze), unsafe_allow_html=True)

# ============================================================
# 1) SOLVE INSTANTLY
# ============================================================
if mode == "Solve Instantly":

    algo = st.selectbox("Algorithm:", ["BFS", "A*"])

    if st.button("Solve Now"):
        out = solve_bfs(maze) if algo == "BFS" else solve_astar(maze)
        solved = parse_maze_string(out)
        st.markdown("### Solved Maze")
        st.markdown(render_color_grid(solved), unsafe_allow_html=True)

    st.stop()

# ============================================================
# 2) VISUALIZE STEP-BY-STEP
# ============================================================
if mode == "Visualize Step-by-Step":

    algo = st.selectbox("Algorithm:", ["BFS", "A*"])

    if st.button("Start Visualization"):
        out = solve_bfs(maze) if algo == "BFS" else solve_astar(maze)
        grid = parse_maze_string(out)

        placeholder = st.empty()
        animated = [[cell for cell in row] for row in grid]

        # Hide the solution initially
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] == "*":
                    animated[r][c] = "T"

        # Reveal path gradually
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] == "*":
                    animated[r][c] = "*"
                placeholder.markdown(render_color_grid(animated), unsafe_allow_html=True)
                time.sleep(0.015)

    st.stop()

# ============================================================
# 3) MANUAL SOLVING — CLICKABLE WASD BUTTONS (NO JAVASCRIPT)
# ============================================================

if mode == "Manual Solving (WASD)":

    st.subheader("Manual Maze Navigation (Clickable WASD Buttons)")

    # Initialize grid if needed
    if "manual_grid" not in st.session_state or st.session_state.manual_grid is None:
        grid = parse_maze_string(maze)

        start = None
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] == "S":
                    start = (r, c)
                    break
            if start:
                break

        st.session_state.player_pos = start
        grid[start[0]][start[1]] = "P"
        st.session_state.manual_grid = grid
        st.session_state.steps = 0

    grid = st.session_state.manual_grid

    MOVE_MAP = {
        "W": (-1, 0),
        "A": (0, -1),
        "S": (1, 0),
        "D": (0, 1),
    }

    def move_player(direction, grid):
        r, c = st.session_state.player_pos
        dr, dc = direction
        nr, nc = r + dr, c + dc

        if nr < 0 or nr >= len(grid) or nc < 0 or nc >= len(grid[0]):
            return grid
        if grid[nr][nc] == "#":
            return grid

        if grid[r][c] == "P":
            grid[r][c] = "T"

        if grid[nr][nc] == "E":
            grid[nr][nc] = "P"
            st.session_state.player_pos = (nr, nc)
            st.session_state.steps += 1
            st.success("Exit reached!")
            return grid

        grid[nr][nc] = "P"
        st.session_state.player_pos = (nr, nc)
        st.session_state.steps += 1
        return grid

    # ---- WASD BUTTON GRID ----

    # Row 1: only W in center
    r1c1, r1c2, r1c3 = st.columns(3)
    if r1c2.button("W", use_container_width=True):
        new_grid = [row[:] for row in grid]
        new_grid = move_player(MOVE_MAP["W"], new_grid)
        st.session_state.manual_grid = new_grid
        st.rerun()

    # Row 2: A (left), empty (center), D (right)
    r2c1, r2c2, r2c3 = st.columns(3)

    if r2c1.button("A", use_container_width=True):
        new_grid = [row[:] for row in grid]
        new_grid = move_player(MOVE_MAP["A"], new_grid)
        st.session_state.manual_grid = new_grid
        st.rerun()

    if r2c3.button("D", use_container_width=True):
        new_grid = [row[:] for row in grid]
        new_grid = move_player(MOVE_MAP["D"], new_grid)
        st.session_state.manual_grid = new_grid
        st.rerun()

    # Row 3: S in the center
    r3c1, r3c2, r3c3 = st.columns(3)
    if r3c2.button("S", use_container_width=True):
        new_grid = [row[:] for row in grid]
        new_grid = move_player(MOVE_MAP["S"], new_grid)
        st.session_state.manual_grid = new_grid
        st.rerun()

    # Render grid
    st.markdown(f"### Steps Taken: {st.session_state.steps}")
    st.markdown(render_color_grid(st.session_state.manual_grid), unsafe_allow_html=True)
    st.stop()


# ============================================================
# 4) ALGORITHM COMPARISON
# ============================================================
if mode == "Algorithm Comparison":

    st.subheader("BFS vs A*")

    bfs_grid = parse_maze_string(solve_bfs(maze))
    astar_grid = parse_maze_string(solve_astar(maze))

    col1, col2 = st.columns(2)

    with col1:
        st.markdown("### BFS")
        st.markdown(render_color_grid(bfs_grid), unsafe_allow_html=True)

    with col2:
        st.markdown("### A*")
        st.markdown(render_color_grid(astar_grid), unsafe_allow_html=True)

    st.stop()

# ============================================================
# 5) MANUAL vs BFS vs A*
# ============================================================
if mode == "Manual vs BFS vs A*":

    if "manual_grid" not in st.session_state or st.session_state.manual_grid is None:
        st.error("No manual path yet — use WASD mode first.")
        st.stop()

    manual = st.session_state.manual_grid
    bfs = parse_maze_string(solve_bfs(maze))
    astar = parse_maze_string(solve_astar(maze))

    c1, c2, c3 = st.columns(3)

    with c1:
        st.markdown("### Manual Path")
        st.markdown(render_color_grid(manual), unsafe_allow_html=True)

    with c2:
        st.markdown("### BFS Path")
        st.markdown(render_color_grid(bfs), unsafe_allow_html=True)

    with c3:
        st.markdown("### A* Path")
        st.markdown(render_color_grid(astar), unsafe_allow_html=True)

    st.stop()
