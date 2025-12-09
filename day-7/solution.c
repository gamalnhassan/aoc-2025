#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COLS 256
#define MAX_ROWS 256

uint64_t walk(uint64_t grid[MAX_COLS][MAX_ROWS],
              bool visited[MAX_COLS][MAX_ROWS], size_t i, size_t j) {
  if (i < 0 || j < 0)
    return 0;
  if (i >= MAX_COLS || j >= MAX_ROWS) {
    return 0;
  }
  if (visited[i][j]) {
    return 0; // dont consider a beam twice
  }
  visited[i][j] = true;
  if (grid[i][j] == 1) {
    return 1 + walk(grid, visited, i - 1, j + 1) +
           walk(grid, visited, i + 1, j + 1);
  }
  return walk(grid, visited, i, j + 1);
}

int main() {
  FILE *fp;

  fp = fopen("/dev/stdin", "r");
  if (fp == NULL) {
    exit(EXIT_FAILURE);
  }

  uint64_t grid[MAX_COLS][MAX_ROWS];
  bool visited[MAX_COLS][MAX_ROWS];

  int c;
  size_t row = 0;
  size_t col = 0;
  size_t cols = 0;
  size_t start_col = 0;
  while ((c = fgetc(fp)) != EOF) {
    switch ((char)c) {
    case '\n':
      cols = col;
      col = 0;
      row++;
      continue;
    case 'S':
      start_col = col;
      break;
    case '^':
      grid[col][row] = 1;
      break;
    }
    col++;
  }

  // Part 1 - Simple recursive approach
  printf("Part 1: %llu\n", walk(grid, visited, start_col, 0));

  // Part 2 - We solve it without recursion
  for (ssize_t j = row - 1; j >= 0; j--) {
    for (size_t i = 0; i < cols; i++) {
      if (grid[i][j] == 0) {
        if (j == MAX_ROWS - 1) {
          continue;
        }
        grid[i][j] = grid[i][j + 1];
      } else {
        uint64_t left = (i == 0 || j == MAX_ROWS - 1) ? 0 : grid[i - 1][j + 1];
        uint64_t right =
            (i == MAX_COLS - 1 || j == MAX_ROWS - 1) ? 0 : grid[i + 1][j + 1];
        grid[i][j] += left + right;
      }
    }
  }

  printf("Part 2: %llu\n", 1 + grid[start_col][0]);
}
