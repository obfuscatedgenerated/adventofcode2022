#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_LEN 32 // maximum length of a string (line in the file)

int main() {
    FILE *handle;

    handle = fopen("01.txt", "r");
    if (handle == NULL) {
        fputs("Error opening file", stderr);
        return 1;
    }

    int current_calories = 0;

    // if this wasn't just a fun event, I'd use a linked list here
    // and a bunch of magic c wizardry, so the program could
    // handle any number of elves
    int record_calories_1st = 0;
    int record_calories_2nd = 0;
    int record_calories_3rd = 0;

    // read the file line by line
    char buffer[MAX_LEN];
    while (fgets(buffer, MAX_LEN, handle) != NULL) {
        // remove the newline character
        buffer[strcspn(buffer, "\n")] = 0;

        if (strcmp(buffer, "") == 0) {
            // new elf!

            if (current_calories > record_calories_1st) { // 1st place
                // shift the other records down by 1
                record_calories_3rd = record_calories_2nd;
                record_calories_2nd = record_calories_1st;

                // set the new record
                record_calories_1st = current_calories;
            } else if (current_calories > record_calories_2nd) { // 2nd place
                // shift the other records down by 1
                record_calories_3rd = record_calories_2nd;

                // set the new record
                record_calories_2nd = current_calories;
            } else if (current_calories > record_calories_3rd) { // 3rd place
                // set the new record
                record_calories_3rd = current_calories;
            }

            current_calories = 0;
            continue;
        }

        // parse the line into a base10 integer
        char *end_ptr;
        int calories = strtol(buffer, &end_ptr, 10);

        if (end_ptr == buffer || *end_ptr != '\0' || calories < 0) { // invalid input check #1
            fprintf(stderr, "Error parsing line: %s", buffer);
            return 1;
        }

        if (calories == 0) { // invalid input check #2
            if (errno == EINVAL) {
                fprintf(stderr, "Conversion error occurred: %d\n", errno);
                return 1;
            }
        }

        current_calories += calories; // add the calories to the current elf
    }

    fclose(handle);

    printf("Record calories (1st): %d\n", record_calories_1st);
    printf("Record calories (2nd): %d\n", record_calories_2nd);
    printf("Record calories (3rd): %d\n", record_calories_3rd);

    printf("Total calories: %d\n", record_calories_1st + record_calories_2nd + record_calories_3rd);
    return 0;
}
