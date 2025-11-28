def parse_maze_string(s):
    lines = [line.strip() for line in s.splitlines() if line.strip()]
    grid = [list(row) for row in lines]
    return grid

def maze_to_string(grid):
    return "\n".join("".join(row) for row in grid)
