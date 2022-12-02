#include <stdio.h>

#define MAX_LEN 32 // maximum length of a string (line in the file)

#define OPP_ROCK 'A'
#define OPP_PAPER 'B'
#define OPP_SCISSORS 'C'

#define PLAYER_ROCK 'X'
#define PLAYER_PAPER 'Y'
#define PLAYER_SCISSORS 'Z'

#define DRAW_BONUS 3
#define WIN_BONUS 6

enum opp_move_e {
    OPP_MOVE_ROCK = OPP_ROCK,
    OPP_MOVE_PAPER = OPP_PAPER,
    OPP_MOVE_SCISSORS = OPP_SCISSORS
};

typedef enum opp_move_e opp_move_et;

enum player_move_e {
    PLAYER_MOVE_ROCK = PLAYER_ROCK,
    PLAYER_MOVE_PAPER = PLAYER_PAPER,
    PLAYER_MOVE_SCISSORS = PLAYER_SCISSORS,
};

typedef enum player_move_e player_move_et;

enum bool_e {
    FALSE = 0,
    TRUE = 1,
};

typedef enum bool_e bool_et;

// there are much better ways to do this, but the task isn't to make the best rps
// probably my enums are defined badly, so I have to do these weird checks

bool_et same_move(player_move_et player, opp_move_et opponent) {
    return ((player == PLAYER_MOVE_ROCK && opponent == OPP_MOVE_ROCK) ||
            (player == PLAYER_MOVE_PAPER && opponent == OPP_MOVE_PAPER) ||
            (player == PLAYER_MOVE_SCISSORS && opponent == OPP_MOVE_SCISSORS));
}

bool_et is_player_winner(player_move_et player, opp_move_et opponent) {
    return ((player == PLAYER_MOVE_ROCK && opponent == OPP_MOVE_SCISSORS) ||
            (player == PLAYER_MOVE_PAPER && opponent == OPP_MOVE_ROCK) ||
            (player == PLAYER_MOVE_SCISSORS && opponent == OPP_MOVE_PAPER));
}

unsigned int get_associated_value(player_move_et player) {
    if (player == PLAYER_MOVE_ROCK) {
        return 1;
    } else if (player == PLAYER_MOVE_PAPER) {
        return 2;
    } else {
        return 3;
    }
}

int main() {
    FILE *handle;

    handle = fopen("02.txt", "r");
    if (handle == NULL) {
        fputs("Error opening file", stderr);
        return 1;
    }

    unsigned int score = 0;

    // read the file line by line
    char buffer[MAX_LEN];
    while (fgets(buffer, MAX_LEN, handle) != NULL) {
        opp_move_et opponent = (unsigned char) buffer[0];
        player_move_et player = (unsigned char) buffer[2];

        score += get_associated_value(player);

        if (same_move(player, opponent)) {
            score += DRAW_BONUS;
        } else if (is_player_winner(player, opponent)) {
            score += WIN_BONUS;
        }
    }

    fclose(handle);

    printf("Score: %d", score);
    return 0;
}