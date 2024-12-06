#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN(x) sizeof(x) / sizeof(x[0])
// not working yet
void err_n_die(bool cond, char *msg) {
  if (!cond)
    return;
  fprintf(stderr, "%s\n", msg);
  exit(EXIT_FAILURE);
}

const char pattern[] = "MAS";
const int dx[] = {1, -1};
const int dy[] = {1, -1};

char line[256], map[256][256];
int ans,w, h;

bool ok(int x, int y) {
    return x >= 0 && x < h && y >= 0 && y < w;
}

bool check_diag(int i, int j, bool up, bool backwards) {
    for (int l = 0; l < (int)strlen(pattern); l++) {
        int x = i + dx[up ? 1 : 0] * (backwards ? strlen(pattern) - 1 - l : l);
        int y = j + dy[up ? 1 : 0] * (backwards ? strlen(pattern) - 1 - l : l);

        if (!ok(x, y) || map[x][y] != pattern[l]) {
            return false;
        }
    }
    return true;
}

bool check_diag_pair(int i, int j) {
    bool down = check_diag(i, j, false, false) || check_diag(i, j, false, true);
    bool up = check_diag(i+2, j+2, true, false) || check_diag(i+2, j+2, true, true);
    return up && down;
}

void solve(void) {
    w = strlen(map[0]);

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w - 2; j++) {
            ans += check_diag_pair(i, j);
        }
    }
}

int main(void) {
    FILE *fp = fopen("./day-04/input.txt", "r");
    err_n_die(fp == NULL, "Couldn't find the input file.");

    while (fgets(line, sizeof(line), fp) != NULL) {
        line[strcspn(line, "\n")] = 0;
        strcpy(map[h++], line);
    }

    solve();
    printf("%d\n", ans);

    fclose(fp);
    return 0;
}
