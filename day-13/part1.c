/*
 *  Part 1 & 2 are not done as of 13.12.2023
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void err_n_die(bool cond, char *msg) {
  if (!cond)
    return;
  fprintf(stderr, "%s\n", msg);
  exit(EXIT_FAILURE);
}

int sum;
char line[512];

void solve(void) {
  // solution here
  sum += 0;
}

int main(void) {
  FILE *fp = fopen("./day-13/example.txt", "r");
  err_n_die(fp == NULL, "Couldn't find the input file.");

  while (fgets(line, sizeof(line), fp) != NULL) {
    solve();
  }

  printf("%d\n", sum);

  fclose(fp);
  return 0;
}
