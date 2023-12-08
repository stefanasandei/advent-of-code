#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

void err_n_die(bool cond, char* msg) {
    if(!cond) return;
    fprintf(stderr, "%s\n", msg);
    exit(EXIT_FAILURE);
}

typedef struct {
    int data[3];
    int size;
} array_t;

char line[256], directions[512], locations[1024][4];
array_t map[262626];
int size;

uint64_t gcd(uint64_t a, uint64_t b) {
    if(b == 0)
        return a;
    return gcd(b, a % b);
}

uint64_t lcm(uint64_t a, uint64_t b) {
    if(a > b)
        return (a / gcd(a,b)) * b;
    return (b / gcd(a, b)) * a;
}

int get_location(char location[]) {
    int index = 0;

    index += 10000 * (location[0] - 'A');
    index += 100 * (location[1] - 'A');
    index += (location[2] - 'A');

    return index;
}

void process_line(void) {
    if(!isalpha(line[0]))
        return;

    char temp[4];
    strncpy(temp, line, 3);
    
    int loc = get_location(temp);
    
    // register the location
    strcpy(locations[size++], temp);

    if(map[loc].data[0] != 0 || map[loc].data[1] != 0) {
        printf("collision detected\n");
        exit(1);
    }
    
    strncpy(temp, line + strlen("AAA = ("), 3);
    map[loc].data[0] = get_location(temp);

    strncpy(temp, line + strlen("AAA = (BBB, "), 3);
    map[loc].data[1] = get_location(temp);
}

uint64_t traverse(char* start) {
    size_t count = 0, step = -1;
    int loc = get_location(start);

    while(loc % 100 != 25) {
        count++;

        // printf("%ld\n", count);

        // issue here with the steps
        if(step+1 == strlen(directions)-1) {
            step = 0;
        } else step++;

        int turn = 0;
        if(directions[step] == 'R')
            turn = 1;

        loc = map[loc].data[turn];

        // printf("step: %ld, loc: %d\n", step, loc);
    }

    // printf("%ld\n", count);

    return count;
}   

void solve(void) {
    uint64_t div = 0;

    for(int i = 0; i < size; i++) {
        if(locations[i][2] != 'A') {
            continue;
        }

        uint64_t count = traverse(locations[i]);
        if(div == 0)
            div = count;
        else div = lcm(div, count);
    }

    printf("%ld\n", div);
}

int main(void) {
    FILE* fp = fopen("./day-08/input.txt", "r");
    err_n_die(fp == NULL, "Couldn't find the input file.");
   
    fgets(directions, sizeof(directions), fp);

    while(fgets(line, sizeof(line), fp) != NULL) {
        process_line();
    }

    solve();

    fclose(fp);
    return 0;
}
