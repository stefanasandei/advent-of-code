/*
 *  Part 1 & 2 are not done as of 12.12.2023
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

// a line is made out of two parts: dots (..##??..) and blocks (the list of
// numbers)
uint32_t sum, dp[1024], blocks[512], n;
char line[512], dots[512];

// i - current position within dots
// j - current position within blocks
// curr - length of current block of '#'
int build(uint32_t i, uint32_t j, uint32_t curr) {
  // TODO: doesn't work yet
  // todo: speed this up using DP

  if (i == strlen(dots) - 1) {
    if (j == n - 1 && curr == 0)
      return 1;
    if (j == n - 2 && blocks[j] == curr)
      return 1;
    return 0;
  }

  int ans = 0;

  const char c[] = {'.', '#', '\0'};
  for (size_t d = 0; d < strlen(c); d++) {
    if (dots[i] == c[d] || dots[i] == '?') {
      if (c[d] == '.' && curr == 0)
        ans += build(i + 1, j, 0);
      else if (c[d] == '.' && curr > 0 && j < n && blocks[j] == curr)
        ans += build(i + 1, j + 1, 0);
      else if (c[d] == '#')
        ans += build(i + 1, j, curr + 1);
    }
  }

  return ans;
}

void solve(void) {
  char *sp = strchr(line, ' ');

  memset(dots, 0, 512);

  // set the dots
  strncpy(dots, line, sp - line);

  // build the blocks
  n = 0;
  // strncpy(blocks, sp + 1, strlen(sp) - 2);
  for (size_t i = 1; i < strlen(sp) - 1; i++) {
    if (sp[i] == ',')
      continue;
    blocks[n++] = sp[i] - '0';
  }

  // printf("%s ", dots);
  // for (int i = 0; i < n; i++)
  //   printf("%d ", blocks[i]);
  // printf("\n");

  sum += build(0, 0, 0);
}

int main(void) {
  FILE *fp = fopen("./day-12/example.txt", "r");
  err_n_die(fp == NULL, "Couldn't find the input file.");

  while (fgets(line, sizeof(line), fp) != NULL) {
    solve();
  }

  printf("%d\n", sum);

  fclose(fp);
  return 0;
}
