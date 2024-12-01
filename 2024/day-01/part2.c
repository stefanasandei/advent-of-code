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

char line[256];
int ans, a, b, v[16384], u[131072], len;

void parse_input(void) {
  sscanf(line, "%d %d", &a, &b);

  v[len++] = a;
  u[b]++;
}

void solve(void) {
  for (int i = 0; i < len; i++) {
    ans += v[i] * u[v[i]];
  }
}

int main(void) {
  FILE *fp = fopen("./day-01/input.txt", "r");
  err_n_die(fp == NULL, "Couldn't find the input file.");

  while (fgets(line, sizeof(line), fp) != NULL) {
    parse_input();
  }

  solve();
  printf("%d\n", ans);

  fclose(fp);
  return 0;
}
