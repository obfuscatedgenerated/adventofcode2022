#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_LEN 64 // maximum length of a string (line in the file)
#define FILE_LEN 300 // file is 300 lines long

#define ALPHA_ORDER "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"

char *find_matching_chars(const char *str1, const char *str2) {
    size_t str1_len = strlen(str1);
    size_t str2_len = strlen(str2);

    int occurences1[CHAR_MAX] = {0};
    int occurences2[CHAR_MAX] = {0};

    for (int i = 0; i < str1_len; i++) {
        occurences1[str1[i]]++;
    }

    for (int i = 0; i < str2_len; i++) {
        occurences2[str2[i]]++;
    }

    char *matching_chars = malloc((CHAR_MAX + 1) * sizeof(char));
    int matching_chars_index = 0;

    for (char i = 0; i < CHAR_MAX; i++) {
        if (occurences1[i] > 0 && occurences2[i] > 0) {
            matching_chars[matching_chars_index] = i;
            matching_chars_index++;
        }
    }

    matching_chars[matching_chars_index] = '\0';

    return matching_chars;
}

size_t get_pos_in_alphabet(char c) {
    for (int i = 0; i < strlen(ALPHA_ORDER); i++) {
        if (ALPHA_ORDER[i] == c) {
            return i;
        }
    }

    return -1;
}

int main() {
    FILE *handle;

    handle = fopen("03.txt", "r");
    if (handle == NULL) {
        fputs("Error opening file", stderr);
        return 1;
    }

    char found_matches[FILE_LEN];
    int found_matches_index = 0;

    // read the file line by line
    char buffer[MAX_LEN];
    while (fgets(buffer, MAX_LEN, handle) != NULL) {
        // remove the newline character
        buffer[strcspn(buffer, "\n")] = 0;

        // split the line in half
        size_t len = strlen(buffer);

        char *first = malloc(len / 2 + 1);
        char *second = malloc(len / 2 + 1);

        strncpy(first, buffer, len / 2); // copy the first half
        first[len / 2] = '\0'; // terminate the string

        strncpy(second, buffer + len / 2, len / 2); // copy the second half
        second[len / 2] = '\0'; // terminate the string

        // find the matching characters
        char *matching_chars = find_matching_chars(first, second);

        // add the matching chars to the found_matches array
        size_t matching_chars_len = strlen(matching_chars);
        for (int i = 0; i < matching_chars_len; i++) {
            found_matches[found_matches_index] = matching_chars[i];
            found_matches_index++;
        }

        free(first);
        free(second);
        free(matching_chars);
    }

    fclose(handle);

    found_matches[found_matches_index] = '\0';

    printf("Found matches: %s\n", found_matches);

    size_t matches_count = found_matches_index;
    size_t total_priority = 0;

    for (int i = 0; i < matches_count; i++) {
        size_t priority = get_pos_in_alphabet(found_matches[i]) + 1; // find position a-z = 1-26, A-Z = 27-52

        if (priority != 0) {
            total_priority += priority;
        } else {
            fprintf(stderr, "Error: %c not found in alphabet!\n", found_matches[i]);
            return 1;
        }
    }

    printf("Total priority: %zu\n", total_priority);
    return 0;
}
