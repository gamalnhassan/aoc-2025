#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROBLEMS 1028
#define MAX_TERMS 4
#define MAX_TERM_LEN 5
#define MAX_LINE_LEN 4096

int main() {
  FILE *fp;

  uint16_t problems[MAX_PROBLEMS][MAX_TERMS];
  size_t terms_offset[MAX_PROBLEMS][MAX_TERMS];
  char ops[MAX_PROBLEMS];
  size_t ops_offset[MAX_PROBLEMS]; // line offset of each operator, gives us
                                   // offset of each problem which we can then
                                   // use to determine the column of each digit
  size_t num_problems = 0;

  fp = fopen("/dev/stdin", "r");
  if (fp == NULL) {
    exit(EXIT_FAILURE);
  }

  char buf[MAX_LINE_LEN];
  char *token;
  size_t read_lines = 0;

  while (fgets(buf, MAX_LINE_LEN, fp)) {
    size_t n = 0;
    token = strtok(buf, " ");
    if (token == NULL) {
      continue;
    }
    while (token) {
      if (*token == '*' || *token == '+') {
        ops[n] = *token;
        ops_offset[n] = (size_t)(token - buf); // get offset from start of line
      } else if (!isspace(token[0])) {
        problems[n][read_lines] = (uint16_t)strtoul(token, NULL, 10);
        terms_offset[n][read_lines] =
            (size_t)(token - buf); // get offset from start of line
        if (read_lines == 0) {
          num_problems++;
        }
      }
      n++;
      token = strtok(NULL, " ");
    }
    read_lines++;
  }

  size_t terms = read_lines - 1;

  uint64_t result[2] = {0, 0};

  for (size_t i = 0; i < num_problems; i++) {

    bool mul = ops[i] == '*';
    // Part 1
    uint16_t identity = mul ? 1 : 0;
    uint64_t res[2] = {identity, identity};
    uint16_t col_terms[MAX_TERM_LEN] = {
        0}; // assuming no 0 in the input terms and that each column contains at
            // least one digit of a term
    for (size_t j = 0; j < terms; j++) {
      uint16_t num = problems[i][j];
      if (num == 0) {
        continue; // assuming no 0 in the input
      }
      if (mul) {
        res[0] *= (uint64_t)num;
      } else {
        res[0] += (uint64_t)num;
      }
      // Part 2
      size_t term_offset = terms_offset[i][j] - ops_offset[i];
      size_t term_len = (size_t)floor(log10(num) + 1);
      for (size_t k = 0; k < term_len; k++) {
        uint16_t digit = num % 10;
        num = (uint16_t)(num / 10);
        size_t idx = term_offset + (term_len - k - 1);

        uint16_t curr_col_term = col_terms[idx];

        col_terms[idx] = (curr_col_term * 10) + digit;
      }
    }
    for (size_t j = 0; j < MAX_TERM_LEN; j++) {
      uint16_t num = col_terms[j];
      if (num == 0) {
        continue; // assuming no 0 in the input
      }
      if (mul) {
        res[1] *= (uint64_t)num;
      } else {
        res[1] += (uint64_t)num;
      }
    }
    result[0] += res[0];
    result[1] += res[1];
  }

  printf("Part 1: %llu\n", result[0]);
  printf("Part 2: %llu\n", result[1]);
}
