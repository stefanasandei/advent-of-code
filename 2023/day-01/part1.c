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

char line[256];
int sum, first, last;

void solve(void) {
    first = last = -1;

    for(char *p = line; *p; p++)
        if(isalpha(*p)) *p = ' ';

    char* token = strtok(line, " ");
    while(token != NULL) {
        if(first == -1 && isdigit(token[0])) 
            first = token[0] - '0';
       
        for(size_t i = strlen(token)-1; i >= 0; i--)
            if(isdigit(token[i])) {
                last = token[i] - '0';
                break;
            }

        token = strtok(NULL, " ");
    }
    
    int num = first * 10 + last;
    sum += num;
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
