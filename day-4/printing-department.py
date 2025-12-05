import fileinput
import time

ts = time.time()

grid: list[list[str]] = []

for line in fileinput.input():
    grid.append([c for c in line.rstrip("\r\n")])

# We assume an n x m grid
n = len(grid)
m = len(grid[0])


def remove_accessible(update_grid: bool = True):
    counter = 0
    for i in range(n):
        for j in range(m):
            if grid[i][j] != "@":
                continue
            dirs = [
                (i - 1, j - 1),
                (i - 1, j),
                (i - 1, j + 1),
                (i, j - 1),
                (i, j + 1),
                (i + 1, j - 1),
                (i + 1, j),
                (i + 1, j + 1),
            ]
            valid_dirs = filter(
                lambda x: x[0] >= 0 and x[0] < n and x[1] >= 0 and x[1] < m, dirs
            )
            neighbors = [grid[_i][_j] for (_i, _j) in valid_dirs]
            if neighbors.count("@") < 4:
                counter += 1
                if update_grid:
                    grid[i][j] = "."
    return counter


counter = remove_accessible(False)
print(f"Part 1: {counter}")

rcounter = 0
while True:
    c = remove_accessible()
    if c == 0:
        break
    rcounter += c

print(f"Part 2: {rcounter}")
