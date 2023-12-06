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

typedef struct {
    int data[256];
    int size;
} array_t;

char line[256], data[3][256];
int prod = 1, len;
array_t times, dists;

void seq_to_array(char* str, int array[], int* len) {
    int num = 0;
    char* token = strtok(str, " ");

    (*len) = 0;

    while(token != NULL) {
        num = 0;
        
        for(size_t i = 0; i < strlen(token); i++) {
            if(!isdigit(token[i]))
                continue;

            int digit = token[i] - '0';
            num = num * 10 + digit;
        }

        array[(*len)++] = num;

        token = strtok(NULL, " ");
    }
}

int calc_dist(int total_t, int pressed_t) {
    return (total_t - pressed_t) * pressed_t;
}

int count_dists(int race_id) {
    int count = 0;

    // check the distance made for each time pressed
    for(int i = 0; i < times.data[race_id]; i++) {
        int dist = calc_dist(times.data[race_id], i);
        if(dist > dists.data[race_id])
            count++;
    }
   
    return count;
}

void solve(void) {
    int start_pos = strlen("Time: ");
    seq_to_array(data[0] + start_pos, times.data, &times.size);

    start_pos = strlen("Distance: ");
    seq_to_array(data[1] + start_pos, dists.data, &dists.size);

    for(int i = 0; i < times.size; i++) {
        prod *= count_dists(i);
    }

    printf("%d\n", prod);
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
