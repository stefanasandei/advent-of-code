#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void err_n_die(bool cond, char *msg) {
  if (!cond)
    return;
  fprintf(stderr, "%s\n", msg);
  exit(EXIT_FAILURE);
}

char line[4096];
int ans;

void solve(void) {
  const size_t len = strlen("mul(");

  for (size_t i = 0; i < strlen(line); i++) {
    if (strncmp(line + i, "mul(", len) != 0) {
      continue;
    }
    i += len;

    if (!isdigit(line[i]))
      continue;

    int a = 0, b = 0;

    while (isdigit(line[i])) {
      a = a * 10 + (line[i] - '0');
      i++;
    }

    if (line[i] != ',')
      continue;
    i++;

    if (!isdigit(line[i]))
      continue;

    while (isdigit(line[i])) {
      b = b * 10 + (line[i] - '0');
      i++;
    }

    if (line[i] != ')')
      continue;

    // printf("%d, %d\n", a, b);
    ans += a * b;
  }
}

int main(void) {
  FILE *fp = fopen("./day-03/input.txt", "r");
  err_n_die(fp == NULL, "Couldn't find the input file.");

  while (fgets(line, sizeof(line), fp) != NULL) {
    solve();
  }

  printf("%d\n", ans);

  fclose(fp);
  return 0;
}
