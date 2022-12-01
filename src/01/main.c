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
    int record_calories = 0;

    // read the file line by line
    char buffer[MAX_LEN];
    while (fgets(buffer, MAX_LEN, handle) != NULL) {
        // remove the newline character
        buffer[strcspn(buffer, "\n")] = 0;

        if (strcmp(buffer, "") == 0) {
            // new elf!

            if (current_calories > record_calories) {
                record_calories = current_calories;
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

    printf("Record calories: %d\n", record_calories);
    return 0;
}
