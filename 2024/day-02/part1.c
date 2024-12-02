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

char line[256];
int ans;

void solve(void) {
  bool is_safe = true;
  int prev = -1, incresing = -1, diff;

  char *token = strtok(line, " ");
  while (token != NULL) {
    int num = 0;
    for (size_t i = 0; i < strlen(token); i++) {
      if (!isdigit(token[i]))
        break;
      num = num * 10 + (token[i] - '0');
    }

    if (prev < 0) {
      prev = num;
    } else {
      diff = abs(num - prev);

      if (diff == 0 || diff > 3) {
        is_safe = false;
        break;
      }

      if (incresing == -1) {
        incresing = (prev < num);
      } else if ((incresing && prev > num) || (!incresing && prev < num)) {
        is_safe = false;
        break;
      }

      prev = num;
    }

    token = strtok(NULL, " ");
  }

  ans += is_safe;
}

int main(void) {
  FILE *fp = fopen("./day-02/input.txt", "r");
  err_n_die(fp == NULL, "Couldn't find the input file.");

  while (fgets(line, sizeof(line), fp) != NULL) {
    solve();
  }

  printf("%d\n", ans);

  fclose(fp);
  return 0;
}
