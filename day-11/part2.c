#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

void err_n_die(bool cond, char *msg) {
  if (!cond)
    return;
  fprintf(stderr, "%s\n", msg);
  exit(EXIT_FAILURE);
}

typedef struct {
  int x, y;
} pair_t;

typedef struct {
  int data[1024];
  int size;
} array_t;

struct {
  pair_t data[1024];
  int size;
} galaxies;

int64_t sum, n, m;
char line[512], map[512][512];
array_t empty_rows, empty_cols;

// returns the distance between the two galaxies
int compute_dists(pair_t a, pair_t b) {
  int fake_dist = abs(a.x - b.x) + abs(a.y - b.y);
  int dist = fake_dist;

  for (int r = 0; r < empty_rows.size; r++) {
    int row = empty_rows.data[r];
    if (MIN(a.x, b.x) <= row && row <= MAX(a.x, b.x))
      dist += (1000000 - 1);
  }

  for (int c = 0; c < empty_cols.size; c++) {
    int col = empty_cols.data[c];
    if (MIN(a.y, b.y) <= col && col <= MAX(a.y, b.y))
      dist += (1000000 - 1);
  }

  return dist;
}

void solve(void) {
  m = strlen(map[0]) - 1;

  // find empty rows & cols
  for (int j = 0; j < m; j++) {
    bool col_empty = true;
    for (int i = 0; i < n; i++) {
      if (map[i][j] == '#') {
        col_empty = false;
        break;
      }
    }
    if (col_empty)
      empty_cols.data[empty_cols.size++] = j;
  }

  for (int i = 0; i < n; i++) {
    bool row_empty = true;

    for (int j = 0; j < m; j++) {
      if (map[i][j] == '#') {
        row_empty = false;

        // add the galaxy
        galaxies.data[galaxies.size++].x = i;
        galaxies.data[galaxies.size - 1].y = j;
      }
    }

    if (row_empty == true)
      empty_rows.data[empty_rows.size++] = i;
  }

  // compute dists - O(n^2)
  for (int i = 0; i < galaxies.size; i++) {
    for (int j = i + 1; j < galaxies.size; j++) {
      sum += compute_dists(galaxies.data[i], galaxies.data[j]);
    }
  }

  printf("%ld\n", sum);
}

int main(void) {
  FILE *fp = fopen("./day-11/input.txt", "r");
  err_n_die(fp == NULL, "Couldn't find the input file.");

  while (fgets(line, sizeof(line), fp) != NULL) {
    strcpy(map[n++], line);
  }

  solve();

  fclose(fp);
  return 0;
}
