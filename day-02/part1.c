#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MAX(a,b) (((a)>(b))?(a):(b))

void err_n_die(bool cond, char* msg) {
    if(!cond) return;
    fprintf(stderr, "%s\n", msg);
    exit(EXIT_FAILURE);
}

typedef struct {
    int id;
    int red, green, blue;
} game_t;

char line[256];
int sum;

void parse_game(game_t* game) {
    char* id_start = line + strlen("Game ");
    char* id_end = strchr(line, ':'); 
    
    for(char* i = id_start; i < id_end; i++) {
        game->id = game->id * 10 + (i[0] - '0');
    }

    // start from id_end and parse groups
    // choose the max value for each color
    char* group = strtok(id_end + 1, ";");
    while(group != NULL) {
        bool started = false;
        int quantity = 0;

        // parse the group
        for(size_t i = 0; i < strlen(group); i++) {
            if(!isdigit(group[i]) && !started)
                continue;

            if(isdigit(group[i]) && !started) {
                started = true;
                quantity = group[i] - '0';
            } else if(isdigit(group[i]) && started) {
                quantity = quantity * 10 + (group[i] - '0');
            } else if(!isdigit(group[i]) && started) {
                started = false;
                
                // figure out what color it is
                switch(group[i+1]) {
                   case 'r':
                        game->red = MAX(game->red, quantity);
                        i += strlen("red");
                        break;
                    case 'g':
                        game->green = MAX(game->green, quantity);
                        i += strlen("green");
                        break;
                    case 'b':
                        game->blue = MAX(game->blue, quantity);
                        i += strlen("blue");
                        break;
                }

                quantity = 0;
            }
        }

        group = strtok(NULL, ";");
    }

    // printf("id = %d; r = %d, g = %d, b = %d\n", game->id, game->red, game->green, game->blue);
}

void solve(void) {
    game_t game = { .red = 0, .green = 0, .blue = 0} ;
    parse_game(&game);

    if(game.red <= 12 && game.green <= 13 && game.blue <= 14)
        sum += game.id;
}

int main(void) {
    FILE* fp = fopen("./day-02/input.txt", "r");
    err_n_die(fp == NULL, "Couldn't find the input file.");
   
    while(fgets(line, sizeof(line), fp) != NULL) {
        solve();
    }

    printf("%d\n", sum);

    fclose(fp);
    return 0;
}
