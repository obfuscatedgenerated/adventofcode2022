#include <stdio.h>

#define MAX_LEN 32 // maximum length of a string (line in the file)

#define OPP_ROCK 'A'
#define OPP_PAPER 'B'
#define OPP_SCISSORS 'C'

#define TARGET_LOSE 'X'
#define TARGET_DRAW 'Y'
#define TARGET_WIN 'Z'

#define DRAW_BONUS 3
#define WIN_BONUS 6

// THIS TIME, XYZ REPRESENTS THE TARGET OUTCOME, LOSE, DRAW, AND WIN RESPECTIVELY
// WE CAN USE OPPONENT TURN ALONGSIDE TARGET OUTCOME TO DETERMINE SCORE

enum opp_move_e {
    OPP_MOVE_ROCK = OPP_ROCK,
    OPP_MOVE_PAPER = OPP_PAPER,
    OPP_MOVE_SCISSORS = OPP_SCISSORS
};

typedef enum opp_move_e opp_move_et;

enum player_move_e {
    PLAYER_MOVE_ROCK = 1,
    PLAYER_MOVE_PAPER = 2,
    PLAYER_MOVE_SCISSORS = 3,
};

typedef enum player_move_e player_move_et;

enum target_result_e {
    RESULT_LOSS = TARGET_LOSE,
    RESULT_DRAW = TARGET_DRAW,
    RESULT_WIN = TARGET_WIN,
};

typedef enum target_result_e target_result_et;

// there are much better ways to do this, but the task isn't to make the best rps
// probably my enums are defined badly, so I have to do these weird checks

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
        target_result_et target_result = (unsigned char) buffer[2];

        // THE MEGA SWITCH!!!
        // messy but fast to code and easy to read :D
        switch (opponent) {
            case OPP_MOVE_ROCK:
                switch (target_result) {
                    case RESULT_LOSS:
                        score += PLAYER_MOVE_SCISSORS;
                        break;
                    case RESULT_DRAW:
                        score += PLAYER_MOVE_ROCK + DRAW_BONUS;
                        break;
                    case RESULT_WIN:
                        score += PLAYER_MOVE_PAPER + WIN_BONUS;
                        break;
                    default:
                        fputs("Invalid move", stderr);
                }
                break;
            case OPP_MOVE_PAPER:
                switch (target_result) {
                    case RESULT_LOSS:
                        score += PLAYER_MOVE_ROCK;
                        break;
                    case RESULT_DRAW:
                        score += PLAYER_MOVE_PAPER + DRAW_BONUS;
                        break;
                    case RESULT_WIN:
                        score += PLAYER_MOVE_SCISSORS + WIN_BONUS;
                        break;
                    default:
                        fputs("Invalid move", stderr);
                }
                break;
            case OPP_MOVE_SCISSORS:
                switch (target_result) {
                    case RESULT_LOSS:
                        score += PLAYER_MOVE_PAPER;
                        break;
                    case RESULT_DRAW:
                        score += PLAYER_MOVE_SCISSORS + DRAW_BONUS;
                        break;
                    case RESULT_WIN:
                        score += PLAYER_MOVE_ROCK + WIN_BONUS;
                        break;
                    default:
                        fputs("Invalid move", stderr);
                }
                break;
            default:
                fputs("Invalid move", stderr);
        }
    }

    fclose(handle);

    printf("Score: %d", score);
    return 0;
}