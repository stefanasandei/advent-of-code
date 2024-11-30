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
    int data[256];
    int size;
} array_t;

char line[256], data[3][256];
int64_t prod = 1, len, time, dist;

void seq_to_num(char* str, int64_t* num) {
    char* token = strtok(str, " ");

    (*num) = 0;

    while(token != NULL) {
        for(size_t i = 0; i < strlen(token); i++) {
            if(!isdigit(token[i]))
                continue;

            int digit = token[i] - '0';
            (*num) = (*num) * 10 + digit;
        }

        token = strtok(NULL, " ");
    }
}

int64_t calc_dist(int64_t total_t, int64_t pressed_t) {
    return (total_t - pressed_t) * pressed_t;
}

int64_t count_dists() {
    int64_t count = 0;

    // check the distance made for each time pressed
    for(int64_t i = 0; i < time; i++) {
        int64_t _dist = calc_dist(time, i);
        if(_dist > dist)
            count++;
    }
   
    return count;
}

void solve(void) {
    int start_pos = strlen("Time: ");
    seq_to_num(data[0] + start_pos, &time);

    start_pos = strlen("Distance: ");
    seq_to_num(data[1] + start_pos, &dist);
    printf("time: %ld\ndist: %ld\n", time, dist);

    prod = count_dists();

    printf("%ld\n", prod);
}

int main(void) {
    FILE* fp = fopen("./day-06/input.txt", "r");
    err_n_die(fp == NULL, "Couldn't find the input file.");
   
    while(fgets(line, sizeof(line), fp) != NULL) {
        strcpy(data[len++], line);
    }

    solve();

    fclose(fp);
    return 0;
}
