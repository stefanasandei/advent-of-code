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

int sum;
char line[256];
array_t series[256];

void seq_to_array(char* str, int array[], int* len) {
    int num = 0, negative = 1;
    char* token = strtok(str, " ");

    (*len) = 0;

    while(token != NULL) {
        num = 0;
        negative = 1;
        
        for(size_t i = 0; i < strlen(token); i++) {
            if(token[i] == '-') {
                negative = -1;
                continue;
            }

            if(!isdigit(token[i]))
                continue;

            int digit = token[i] - '0';
            num = num * 10 + digit;
        }

        array[(*len)++] = negative * num;

        token = strtok(NULL, " ");
    }
}

void solve(void){
    seq_to_array(line, series[0].data, &series[0].size);

    int last = series[0].data[series[0].size-1], step = 0;
    do {
        step++;
        
        series[step].size = series[step-1].size - 1;

        for(int i = 0; i < series[step].size; i++)
            series[step].data[i] = series[step-1].data[i+1] - series[step-1].data[i];

        last = series[step].data[series[step].size-1];
    } while(last != 0);

    int local_sum = 0;
    for(int i = 0; i <= step; i++) {
        local_sum += series[i].data[series[i].size-1];
        /*printf("%d: ", i);
        for(int j = 0; j < series[i].size; j++)
            printf("%d, ", series[i].data[j]);
        printf("\n");*/
    }

    sum += local_sum;
}

int main(void) {
    FILE* fp = fopen("./day-09/input.txt", "r");
    err_n_die(fp == NULL, "Couldn't find the input file.");
   
    while(fgets(line, sizeof(line), fp) != NULL) {
        solve();
    }

    printf("%d\n", sum);

    fclose(fp);
    return 0;
}
