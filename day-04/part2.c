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

char line[256], temp[256];
int sum, w, winning[256], o, owns[256], total, copies[256];

void collect_cards(int start_pos, int end_pos, int cards[], int* len) {
    strncpy(temp, line + start_pos, end_pos - start_pos);

    (*len) = 0;

    char* token = strtok(temp, " \n");
    while(token != NULL) {

        int num = 0;
        for(size_t i = 0; i < strlen(token); i++) {
            if(!isdigit(token[i]))
                continue;
            int digit = token[i] - '0';
            num = num * 10 + digit;
        }

        cards[(*len)++] = num;

        token = strtok(NULL, " \n");
    }
}

void solve(void) {
    int matches = 0;

    copies[total++] += 1;

    int start = strchr(line, ':') - line;
    int end = strchr(line, '|') - line;

    collect_cards(start+1, end-1, winning, &w);
    collect_cards(end+1, strlen(line)-1, owns, &o);

    // O(n^2) - search for winning cards
    for(int i = 0; i < o; i++) {
        bool found = false;
        
        for(int j = 0; j < w; j++) {
            if(winning[j] == owns[i]) {
                found = true;
                break;
            }
        }

        if(found) {
            matches++;
        }
    }

    for(int card = 0; card < matches; card++) {
        int card_index = (total - 1) + (card + 1);
        copies[card_index] += copies[total-1];
        
        // printf("%d from %d = %d\n", card_index+1, total, copies[card_index]);
    }
}

int main(void) {
    FILE* fp = fopen("./day-04/input.txt", "r");
    err_n_die(fp == NULL, "Couldn't find the input file.");
  
    while(fgets(line, sizeof(line), fp) != NULL) {
        solve();
    }

    for(int i=0; i<total; i++) {
        // printf("[%d] = %d\n", i+1, copies[i]);
        sum += (copies[i]);
    }
    printf("%d\n", sum);

    fclose(fp);
    return 0;
}
