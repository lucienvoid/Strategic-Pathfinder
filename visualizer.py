import time
import streamlit as st
from maze_utils import parse_maze_string, maze_to_string
import heapq
from collections import deque

# ----------------------------------------------------
# COLOR GRID RENDERING (PRIMARY VISUALIZER)
# ----------------------------------------------------

def render_color_grid(grid):
    color_map = {
        '#': '#222222',
        '.': '#FFFFFF',
        'S': '#2563EB',
        'E': '#16A34A',
        '*': '#FACC15',
        'V': '#9333EA',
        'Q': '#F97316',
        'P': '#3B82F6',
        'T': '#9CA3AF',
    }

    html = "<div style='line-height:0.8;'>"
    for row in grid:
        for cell in row:
            color = color_map.get(cell, "#FFFFFF")
            html += (
                f"<span style='display:inline-block;width:18px;height:18px;"
                f"background:{color};border-radius:3px;margin:1px;'></span>"
            )
        html += "<br>"
    html += "</div>"
    return html


def animate_frames(frames, delay=0.05):
    import streamlit as st
    for grid in frames:
        st.markdown(render_color_grid(grid), unsafe_allow_html=True)
        time.sleep(delay)


# BFS & A* visualizers must already exist; I’m leaving your working versions untouched

# ----------------------------------------------------
# BASIC TEXT GRID (fallback)
# ----------------------------------------------------

COLOR_MAP = {
    '#': '🟥',
    '.': '⬜',
    'S': '🟦',
    'E': '🟩',
    '*': '🟨',
    'V': '🟪',
    'Q': '🟧',
}

def render_grid(grid):
    out = ""
    for row in grid:
        for cell in row:
            out += COLOR_MAP.get(cell, cell) + " "
        out += "\n"
    return out

# ----------------------------------------------------
# FRAME ANIMATION ENGINE
# ----------------------------------------------------

def animate_frames(frames, delay=0.05):
    placeholder = st.empty()

    for frame in frames:
        grid = parse_maze_string(frame)
        html = render_color_grid(grid)
        placeholder.markdown(html, unsafe_allow_html=True)
        time.sleep(delay)

# ----------------------------------------------------
# BFS VISUALIZATION
# ----------------------------------------------------

def bfs_visualize(maze_str):
    grid = parse_maze_string(maze_str)
    rows, cols = len(grid), len(grid[0])

    start = end = None
    for r in range(rows):
        for c in range(cols):
            if grid[r][c] == 'S':
                start = (r, c)
            if grid[r][c] == 'E':
                end = (r, c)

    q = deque([start])
    visited = set([start])
    parent = {}
    frames = []

    def snapshot():
        frames.append(maze_to_string(grid))

    dirs = [(-1,0), (1,0), (0,-1), (0,1)]

    snapshot()

    while q:
        r, c = q.popleft()

        if (r, c) != start and grid[r][c] not in "SE":
            grid[r][c] = 'V'
        snapshot()

        if (r, c) == end:
            cur = end
            while cur != start:
                rr, cc = cur
                if grid[rr][cc] not in "SE":
                    grid[rr][cc] = '*'
                snapshot()
                cur = parent[cur]
            return frames

        for dr, dc in dirs:
            nr, nc = r + dr, c + dc
            if 0 <= nr < rows and 0 <= nc < cols and grid[nr][nc] != '#' and (nr, nc) not in visited:
                visited.add((nr, nc))
                parent[(nr, nc)] = (r, c)
                if grid[nr][nc] not in "SE":
                    grid[nr][nc] = 'Q'
                q.append((nr, nc))
                snapshot()

    return frames

# ----------------------------------------------------
# A* VISUALIZATION
# ----------------------------------------------------

def astar_visualize(maze_str):
    grid = parse_maze_string(maze_str)
    rows, cols = len(grid), len(grid[0])

    start = end = None
    for r in range(rows):
        for c in range(cols):
            if grid[r][c] == 'S':
                start = (r, c)
            if grid[r][c] == 'E':
                end = (r, c)

    def h(a, b):
        return abs(a[0] - b[0]) + abs(a[1] - b[1])

    g = {start: 0}
    f = {start: h(start, end)}
    parent = {}

    open_list = []
    heapq.heappush(open_list, (f[start], start))
    visited = set()
    frames = []

    dirs = [(-1,0), (1,0), (0,-1), (0,1)]

    def snapshot():
        frames.append(maze_to_string(grid))

    snapshot()

    while open_list:
        _, current = heapq.heappop(open_list)
        if current in visited:
            continue
        visited.add(current)

        r, c = current
        if current != start and grid[r][c] not in "SE":
            grid[r][c] = 'V'
        snapshot()

        if current == end:
            cur = end
            while cur != start:
                rr, cc = cur
                if grid[rr][cc] not in "SE":
                    grid[rr][cc] = '*'
                snapshot()
                cur = parent[cur]
            return frames

        for dr, dc in dirs:
            nr, nc = r + dr, c + dc
            if 0 <= nr < rows and 0 <= nc < cols and grid[nr][nc] != '#':
                tentative_g = g[current] + 1

                if (nr, nc) not in g or tentative_g < g[(nr, nc)]:
                    g[(nr, nc)] = tentative_g
                    f[(nr, nc)] = tentative_g + h((nr, nc), end)
                    parent[(nr, nc)] = current

                    if grid[nr][nc] not in "SE":
                        grid[nr][nc] = 'Q'

                    heapq.heappush(open_list, (f[(nr, nc)], (nr, nc)))
                    snapshot()

    return frames

# ----------------------------------------------------
# BFS HEATMAP (Optional)
# ----------------------------------------------------

def bfs_heatmap(maze_str):
    grid = parse_maze_string(maze_str)
    rows, cols = len(grid), len(grid[0])

    start = None
    for r in range(rows):
        for c in range(cols):
            if grid[r][c] == 'S':
                start = (r, c)
                break

    if not start:
        return ""

    dist = [[None for _ in range(cols)] for _ in range(rows)]
    q = deque([start])
    dist[start[0]][start[1]] = 0

    dirs = [(-1,0), (1,0), (0,-1), (0,1)]

    while q:
        r, c = q.popleft()
        for dr, dc in dirs:
            nr, nc = r + dr, c + dc
            if 0 <= nr < rows and 0 <= nc < cols and grid[nr][nc] != '#':
                if dist[nr][nc] is None:
                    dist[nr][nc] = dist[r][c] + 1
                    q.append((nr, nc))

    heat = ""
    for r in range(rows):
        for c in range(cols):
            heat += ("██ " if dist[r][c] is None else f"{dist[r][c] % 10} ")
        heat += "\n"

    return heat
