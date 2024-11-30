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

typedef enum {
    FIVE_OF_A_KIND,  // AAAAA
    FOUR_OF_A_KIND,  // AA8AA
    FULL_HOUSE,      // 23332
    THREE_OF_A_KIND, // TTT98
    TWO_PAIR,        // 22334
    ONE_PAIR,        // AA234
    HIGH_CARD        // 23456
} type_t;

typedef struct {
    // a hand is a list of card labels (chars)
    // a hand has one type and each label has a strength
    // type > label strength
    char hand[6]; 
    type_t type;

    // multiply the bid with the hand rank (its order)
    int bid;
} pair_t;

// A is the highest and 2 is the lowest
// actually needs to be in reversed order labels['A'] > labels['2'] ?
const char opts[] = { 
    '2', '3', '4', '5', '6', '7', '8', '9', 
    'T', 'J', 'Q', 'K', 'A', '\0'
};


int size, labels[82], frecv[82];
char line[256];
pair_t game[4096];
uint64_t sum;

void init(void) {
    int strength = 1;

    for(size_t i = 0; i < strlen(opts); i++) 
        labels[(int)opts[i]] = (strength++);
}

// from 0 to 6 (reversed, the strongest have the biggest id)
type_t get_hand_type(char hand[]) {
    for(int i = '2'; i <= 'T'; i++)
        frecv[i] = 0;

    for(size_t i = 0; i < strlen(hand); i++)
        frecv[(int)hand[i]]++;
    
    bool found3 = false; // AAA
    int found2 = 0; // AA

    for(size_t i = '2'; i <= 'T'; i++) {
        if(frecv[i] == 0) continue;
        
        if(frecv[i] == 2) 
            found2++;

        if(frecv[i] == 5)
            return FIVE_OF_A_KIND;
        else if(frecv[i] == 4)
            return FOUR_OF_A_KIND;
        else if(frecv[i] == 3) {
            found3 = true;
        }
    }

    if(found2 == 1 && found3)
        return FULL_HOUSE;
    if(found2 == 0 && found3)
        return THREE_OF_A_KIND;
    if(found2 == 2)
        return TWO_PAIR;
    if(found2 == 1)
        return ONE_PAIR;

    return HIGH_CARD;
}

// first type and then the strength of each card
bool is_stronger(pair_t a, pair_t b) {
    if(a.type != b.type)
        return a.type > b.type;
    
    for(size_t i = 0; i < strlen(a.hand); i++) {
        if(a.hand[i] == b.hand[i])
            continue;
        
        return labels[(int)a.hand[i]] < labels[(int)b.hand[i]];
    }

    // they're the same
    return false;
}

void process_line(void) {
    // firt split by space
    // then read the hand & compute kind
    // read the bid
    // add the pair to the game

    char* split_pos = strchr(line, ' ');
    strncpy(game[size].hand, line, split_pos - line);
    
    game[size].type = get_hand_type(game[size].hand);

    // split_pos + 1 to int
    int num = 0;
    for(size_t i = 1; i < strlen(split_pos) - 1; i++) {
        int digit = split_pos[i] - '0';
        num = num * 10 + digit;
    }

    game[size].bid = num;

    // printf("%s, %d, %d\n", game[size].hand, game[size].type, game[size].bid);

    size++;
}

void solve(void) {
    // order pairs based on the strength of the cards
    // then iterate over cards and add to the sum bid * index

    // bubble sort the pairs
    bool sorted = false;
    while(!sorted) {
        sorted = true;

        for(int i = 0; i < size - 1; i++) {
            if(is_stronger(game[i+1], game[i])) {
                // swap cards
                pair_t temp = game[i+1];
                game[i+1] = game[i];
                game[i] = temp;

                sorted = false;
            }
        }
    }

    // iterate from start to finish and add to the sum
    for(int i = 0; i < size; i++) {
        // printf("%s\n", game[i].hand);
        sum += game[i].bid * (i+1);
    }

    printf("%ld\n", sum);
}

int main(void) {
    FILE* fp = fopen("./day-07/input.txt", "r");
    err_n_die(fp == NULL, "Couldn't find the input file.");
  
    init();

    while(fgets(line, sizeof(line), fp) != NULL) {
        process_line();
    }

    solve();

    fclose(fp);
    return 0;
}
