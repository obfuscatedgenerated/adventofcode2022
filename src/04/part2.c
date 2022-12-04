#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_LEN 32 // maximum length of a string (line in the file)
#define FILE_LEN 1000 // file is 1000 lines long

int main() {
    FILE *handle;

    handle = fopen("04.txt", "r");
    if (handle == NULL) {
        fputs("Error opening file", stderr);
        return 1;
    }

    unsigned int overlaps = 0;

    // read the file line by line
    char buffer[MAX_LEN];
    while (fgets(buffer, MAX_LEN, handle) != NULL) {
        // remove the newline character
        buffer[strcspn(buffer, "\n")] = 0;

        // split line into 2 by comma
        char *elf1 = strtok(buffer, ",");
        char *elf2 = strtok(NULL, ",");

        // split each string by the dash
        char *elf1_start = strtok(elf1, "-");
        char *elf1_end = strtok(NULL, "-");

        char *elf2_start = strtok(elf2, "-");
        char *elf2_end = strtok(NULL, "-");

        // convert strings to ints
        unsigned int elf1_start_int = strtol(elf1_start, NULL, 10);
        unsigned int elf1_end_int = strtol(elf1_end, NULL, 10);

        unsigned int elf2_start_int = strtol(elf2_start, NULL, 10);
        unsigned int elf2_end_int = strtol(elf2_end, NULL, 10);

        // check if the ranges overlap AT ALL
        if (elf1_start_int <= elf2_start_int && elf1_end_int >= elf2_start_int || elf2_start_int <= elf1_start_int && elf2_end_int >= elf1_start_int) {
            overlaps++;
        }
    }

    fclose(handle);

    printf("Overlaps: %d", overlaps);
    return 0;
}
