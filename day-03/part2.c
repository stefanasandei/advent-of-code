#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

void err_n_die(bool cond, char* msg) {
    if(!cond) return;
    fprintf(stderr, "%s\n", msg);
    exit(EXIT_FAILURE);
}

const int dx[] = {-1, 0, 1, 0, 1, -1, 1, -1};
const int dy[] = {0, 1, 0, -1, -1, 1, 1, -1}; 

int sum, height, size, parts, gears[256];
char line[256], schematic[256][256];

bool issymbol(char c) {
    const bool symbol = !isdigit(c) && !isalpha(c) && isgraph(c);
    return symbol && c != '.';
}

bool inside(int x, int y) {
    return x >= 0 && x < height && y >= 0 && y < size;
}

int get_number(int x, int y) {
    // get as far to the left as possible (--)
    // construct the number from there
    // change to '.' once we made the number

    while(isdigit(schematic[x][y]) && y >= 0)
        y--;

    int number = 0;
    while(isdigit(schematic[x][y+1])) {
        number = number * 10 + (schematic[x][y+1] - '0');
        schematic[x][y+1] = '.';
        y++;
    }

    return number;
}

void solve(void){
    size = strlen(schematic[0]);

    for(int i = 0; i < height; i++) {
        for(int j = 0; j < size; j++) {
            if(!issymbol(schematic[i][j]))
                continue;
            
            parts = 0;

            // check neighbours
            for(int k = 0; k < 8; k++) {
                int x = i + dx[k];
                int y = j + dy[k];

                if(!inside(x, y) || !isdigit(schematic[x][y]))
                    continue;

                int d = get_number(x, y);
                // printf("(%d, %d) = %d %c\n", x, y, d, schematic[i][j]);
                gears[parts++] = d;
            }

            if(parts != 2)
                continue;

            // printf("%d, %d\n", gears[0], gears[1]);
            sum += (gears[0] * gears[1]);
        }
    }

    printf("%d\n", sum);
}

int main(void) {
    FILE* fp = fopen("./day-03/input.txt", "r");
    err_n_die(fp == NULL, "Couldn't find the input file.");
   
    while(fgets(line, sizeof(line), fp) != NULL) {
        strcpy(schematic[height++], line);
    }

    solve();

    fclose(fp);
    return 0;
}
