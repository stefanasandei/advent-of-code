#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN(x) sizeof(x) / sizeof(x[0])

void err_n_die(bool cond, char *msg) {
  if (!cond)
    return;
  fprintf(stderr, "%s\n", msg);
  exit(EXIT_FAILURE);
}

const int dx[] = {0, 1, 1, 1, 0, -1, -1, -1};
const int dy[] = {-1, -1, 0, 1, 1, 1, 0, -1};

char line[256], map[256][256];
int ans,w, h;

bool ok(int x, int y) {
    return x >= 0 && x < w && y >= 0 && y < h;
}

void solve(void) {
    const char pattern[] = "XMAS";
    w = strlen(map[0]);

    for(int i=0; i<h; i++) {
        for(int j=0; j<w; j++) {
            for(size_t k = 0; k < LEN(dx); k++) {
                bool found = true;

                for(size_t l=0; l < strlen(pattern) && found; l++) {
                    int x = i + dx[k] * l;
                    int y = j + dy[k] * l;

                    if(!ok(x, y)) {
                        found = false;
                    } else {
                        found = pattern[l] == map[x][y];
                    }
                }

                ans += found;
            }
        }
    }
}

int main(void) {
  FILE *fp = fopen("./day-04/input.txt", "r");
  err_n_die(fp == NULL, "Couldn't find the input file.");

  while (fgets(line, sizeof(line), fp) != NULL) {
      strcpy(map[h++], line);
  }

  solve();
  printf("%d\n", ans);

  fclose(fp);
  return 0;
}
