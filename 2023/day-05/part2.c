/*
 *  Part 2 is not done!
 *  still needs work for an optimal solution with ranges
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <limits.h>

#define MIN(a,b) (((a)<(b))?(a):(b))

void err_n_die(bool cond, char* msg) {
    if(!cond) return;
    fprintf(stderr, "%s\n", msg);
    exit(EXIT_FAILURE);
}

typedef struct {
    uint64_t data[256];
    int size;
} array_t;

typedef struct {
    uint64_t begin, end;
} range_t;

char line[256], almanac[256][256];
int seeds_size, almanac_size, mapped[256];
array_t map;
range_t seeds;

uint64_t min = ULLONG_MAX;

void seq_to_array(char* str, uint64_t array[], int* len) {
    int64_t num = 0;
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

void init_seeds(void) {
    int start_pos = strlen("seeds: ");

    array_t seed_ranges;

    seq_to_array(almanac[0] + start_pos, seed_ranges.data, &seed_ranges.size);

    for(int i = 0; i < seed_ranges.size; i+=2) {
        seeds[seeds_size++].begin = seed_ranges.data[i];
        seeds[seeds_size].end = seed_range.data[i] + seed_ranges.data[i+1];
    }
}

void parse_map(char line_map[]) {
    seq_to_array(line_map, map.data, &map.size);

    uint64_t destination = map.data[0], 
             source = map.data[1], 
             range = map.data[2];

    for(int i = 0; i < seeds.size; i++) {
        if(mapped[i])
            continue;

        if(seeds.data[i] >= source && seeds.data[i] < source + range) {
            uint64_t dist = seeds.data[i] - source;
            seeds.data[i] = destination + dist;
            mapped[i] = true;
        }
    }
}

void solve(void) {
    init_seeds(); 
    // now input seeds are in pairs (start, range size)
    
    // TODO from here
    for(int i = 1; i < almanac_size; i++) {
        if(strstr(almanac[i], "map:") == NULL) {
            parse_map(almanac[i]);
        } else {
            // printf("------------\n");

            for(int i = 0; i < seeds.size; i++)
                mapped[i] = false;
        }

        /*for(int i = 0; i < seeds.size; i++) {
            printf("%ld, ", seeds.data[i]);
        }
        printf("\n");*/
    }

    for(int i = 0; i < seeds.size; i++)
        min = MIN(min, seeds.data[i]);

    printf("%ld\n", min);
}

int main(void) {
    FILE* fp = fopen("./day-05/example.txt", "r");
    err_n_die(fp == NULL, "Couldn't find the input file.");
   
    while(fgets(line, sizeof(line), fp) != NULL) {
        if(line[0] == '\n')
            continue;

        strcpy(almanac[almanac_size++], line);
    }

    solve();

    fclose(fp);
    return 0;
}
