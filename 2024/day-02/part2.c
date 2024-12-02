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
int ans, arr[1024], len;

void solve(void) {
  bool is_safe = true;

  len = 0;

  char *token = strtok(line, " ");
  while (token != NULL) {
    int num = 0;
    for (size_t i = 0; i < strlen(token); i++) {
      if (!isdigit(token[i]))
        break;
      num = num * 10 + (token[i] - '0');
    }

    arr[len++] = num;

    token = strtok(NULL, " ");
  }

  for (int i = -1; i < len; i++) {
    int prev = -1, incresing = -1, diff;
    is_safe = true;

    for (int j = 0; j < len; j++) {
      if (j == i)
        continue;

      if (prev < 0) {
        prev = arr[j];
      } else {
        diff = abs(arr[j] - prev);

        if (diff == 0 || diff > 3) {
          is_safe = false;
          break;
        }

        if (incresing == -1) {
          incresing = (prev < arr[j]);
        } else if ((incresing && prev > arr[j]) ||
                   (!incresing && prev < arr[j])) {
          is_safe = false;
          break;
        }

        prev = arr[j];
      }
    }

    if (is_safe)
      break;
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
