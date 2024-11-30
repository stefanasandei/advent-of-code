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

const char* digits_table[] = { 
    "zero", "one", "two", "three",
    "four", "five", "six", "seven",
    "eight", "nine"
};

char line[256], token[256];
int sum, first, last, tlen;

int get_digit_value(char* s) {
    for(int i = 0; i < 10; i++) {
        if(strcmp(s, digits_table[i]) == 0)
            return i;
    }
    return -1;
}

void solve(void) {
    size_t first_index = strlen(line) + 1;
    first = last = -1;

    for(size_t i = 0; i < strlen(line); i++) {
        tlen = 0;

        for(size_t j = i; j < strlen(line); j++) {
            if(isdigit(line[j])) {
                if(j < first_index) {
                    first = line[j] - '0';
                    first_index = j;
                }
                last = line[j] - '0';
                break;
            }

            token[tlen++] = line[j];
            token[tlen] = '\0';
        
            int digit = get_digit_value(token);
            if(digit != -1) {
                if(i < first_index) {
                    first = digit;
                    first_index = i;
                }
                last = digit;
            }
        }
    }
    
    sum += first * 10 + last;
}

int main(void) {
    FILE* fp = fopen("./day-01/input.txt", "r");
    err_n_die(fp == NULL, "Couldn't find the input file.");
    
    while(fgets(line, sizeof(line), fp) != NULL) {
        solve();
    }

    printf("%d\n", sum);

    fclose(fp);
    return 0;
}
