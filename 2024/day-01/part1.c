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
int ans, a, b, v[16384], u[16384], len;

void sort_arr(int arr[], int len) {
  bool sorted = false;

  while (!sorted) {
    sorted = true;

    for (int i = 0; i < len - 1; i++) {
      if (arr[i] > arr[i + 1]) {
        sorted = false;

        int temp = arr[i];
        arr[i] = arr[i + 1];
        arr[i + 1] = temp;
      }
    }
  }
}

void parse_input(void) {
  sscanf(line, "%d %d", &a, &b);

  v[len] = a;
  u[len] = b;
  len++;
}

void solve(void) {
  sort_arr(v, len);
  sort_arr(u, len);

  for (int i = 0; i < len; i++) {
    ans += abs(v[i] - u[i]);
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
