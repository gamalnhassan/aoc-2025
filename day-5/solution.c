#include <stdio.h>
#include <stdlib.h>

#define RANGES_COUNT 174
#define IDS_COUNT 1000
#define LONG_LEN sizeof(uint64_t) * 8

int compare_ranges(const void *a, const void *b) {
  uint64_t long_a = ((const uint64_t *)a)[0];
  uint64_t long_b = ((const uint64_t *)b)[0];
  if (long_a == long_b)
    return 0;
  return long_a < long_b ? -1 : 1;
}

int main() {
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  uint64_t ranges[RANGES_COUNT][2];
  size_t num_ranges = 0;

  uint64_t ids[IDS_COUNT];
  size_t num_ids = 0;

  fp = fopen("input.txt", "r");
  if (fp == NULL) {
    exit(EXIT_FAILURE);
  }

  while ((read = getline(&line, &len, fp)) != -1) {
    if (line == NULL) {
      exit(EXIT_FAILURE);
    }
    if (line[0] == '\n') {
      break;
    }
    size_t delim = 0;
    while (line[delim] != '-') {
      delim++;
    }

    line[delim] = '\0';
    ranges[num_ranges][0] = atol(line);
    ranges[num_ranges][1] = atol(line + delim + 1);

    num_ranges++;
  }

  while ((read = getline(&line, &len, fp)) != -1) {
    if (line == NULL) {
      exit(EXIT_FAILURE);
    }
    ids[num_ids++] = atol(line);
  }

  qsort(ranges, num_ranges, sizeof(uint64_t[2]), compare_ranges);

  // Coalesce the ranges
  uint64_t lo, hi = 0;
  uint64_t curr_lo = ranges[0][0];
  uint64_t curr_hi = ranges[0][1];

  uint64_t coalesced_ranges[RANGES_COUNT][2];
  size_t num_coal_ranges = 0;

  uint64_t total_range = 0; // Part 2

  for (size_t i = 1; i < num_ranges; i++) {
    lo = ranges[i][0];
    hi = ranges[i][1];
    if (lo <= curr_hi && hi > curr_hi) {
      curr_hi = hi;
    } else if (lo > curr_hi) {
      coalesced_ranges[num_coal_ranges][0] = curr_lo;
      coalesced_ranges[num_coal_ranges++][1] = curr_hi;
      total_range += curr_hi - curr_lo + 1;
      curr_lo = lo;
      curr_hi = hi;
    }
  }
  coalesced_ranges[num_coal_ranges][0] = curr_lo;
  coalesced_ranges[num_coal_ranges++][1] = curr_hi;
  total_range += curr_hi - curr_lo + 1;

  size_t valid_ids = 0; // Part 1
  for (size_t i = 0; i < num_ids; i++) {
    uint64_t id = ids[i];
    for (size_t j = 0; j < num_coal_ranges; j++) {
      if (coalesced_ranges[j][0] > id) {
        break;
      }
      if (coalesced_ranges[j][1] >= id) {
        valid_ids++;
        break;
      }
    }
  }

  printf("Part 1: %zu\n", valid_ids);
  printf("Part 2: %llu\n", total_range);
}
