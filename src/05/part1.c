#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 64 // maximum length of a string (line in the file)
#define HEAD_LEN 9 // file is 9 lines long
#define MOVE_LEN 501 // file is 501 lines long

void reverse(char arr[], unsigned int n) {
    char reversed[n];

    for (unsigned int i = 0; i < n; i++) {
        reversed[n - 1 - i] = arr[i];
    }

    for (unsigned int i = 0; i < n; i++) {
        arr[i] = reversed[i];
    }
}


int main() {
    FILE *head_handle;

    head_handle = fopen("05-head.txt", "r");
    if (head_handle == NULL) {
        fputs("Error opening file", stderr);
        return 1;
    }

    char crates[HEAD_LEN][MAX_LEN] = {0}; // 9 bays of up to 32 blocks

    // read the file line by line
    char head_buffer[MAX_LEN];
    int line = 0;
    while (fgets(head_buffer, MAX_LEN, head_handle) != NULL) {
        // remove the newline character
        head_buffer[strcspn(head_buffer, "\n")] = 0;

        strncpy(crates[line], head_buffer, MAX_LEN);
        line++;
    }

    fclose(head_handle);

    FILE *move_handle;

    move_handle = fopen("05-moves.txt", "r");
    if (move_handle == NULL) {
        fputs("Error opening file", stderr);
        return 1;
    }

    char move_buffer[MAX_LEN];
    int move_idx = 0;
    while (fgets(move_buffer, MAX_LEN, move_handle) != NULL) {
        move_idx++;
        // remove the newline character
        move_buffer[strcspn(move_buffer, "\n")] = 0;

        // remove leading word "move"
        char *move = move_buffer + 5;

        // split line by "from" to get number of crates
        char *crates_str = strtok(move, " from ");

        // split line by "to" to get source and destination
        char *source_str = strtok(NULL, " from ");
        char *destination_str = strtok(NULL, " to ");

        // convert strings to ints
        unsigned int crates_int = strtol(crates_str, NULL, 10);

        unsigned int source_int = strtol(source_str, NULL, 10) - 1;
        unsigned int destination_int = strtol(destination_str, NULL, 10) - 1;

        unsigned int src_height = strlen(crates[source_int]);

        // pickup the crates with a stack and remove them from the source
        char stack[crates_int];
        strncpy(stack, crates[source_int] + src_height - crates_int, crates_int);
        strncpy(crates[source_int] + src_height - crates_int, "\0", crates_int);

        reverse(stack, crates_int);

        // dump the crates onto the destination
        strncat(crates[destination_int], stack, crates_int);

        // print the crates
        for (unsigned int i = 0; i < HEAD_LEN; i++) {
            printf("%d | %s\n", (i + 1), crates[i]);
        }
    }
}