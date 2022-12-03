#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_LEN 64 // maximum length of a string (line in the file)
#define FILE_LEN 300 // file is 300 lines long

#define ALPHA_ORDER "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"

enum bool_e {
    FALSE = 0,
    TRUE = 1,
};

typedef enum bool_e bool_et;

bool_et contains_char(const char *str, char c, size_t string_len) {
    for (int i = 0; i < string_len; i++) {
        if (str[i] == c) {
            return TRUE;
        }
    }

    return FALSE;
}

char *find_matching_chars(const char *str1, const char *str2, size_t string_len) {
    char *matching_chars = malloc(string_len * sizeof(char));
    int matching_chars_index = 0;

    // first pass, compare string1's chars to string2
    for (int i = 0; i < string_len; i++) {
        if(contains_char(str2, str1[i], string_len)) {
            // check if the char is already in the matching_chars array
            if (!contains_char(matching_chars, str1[i], string_len)) {
                matching_chars[matching_chars_index] = str1[i];
                matching_chars_index++;
            }
        }
    }

    // not required! it would be common to both strings!
    // second pass, compare string2's chars to string1
    //for (int i = 0; i < string_len; i++) {
    //    if(contains_char(str1, str2[i], string_len)) {
    //        // check if the char is already in the matching_chars array
    //        if (!contains_char(matching_chars, str2[i], string_len)) {
    //            matching_chars[matching_chars_index] = str2[i];
    //            matching_chars_index++;
    //        }
    //    }
    //}

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

    char *found_matches = malloc((FILE_LEN + 1) * sizeof(char));

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
        char *matching_chars = find_matching_chars(first, second, len / 2);

        // add the matching chars to the found_matches array
        if (strcmp(found_matches, "") == 0) {
            strcpy(found_matches, matching_chars);
        } else {
            strcat(found_matches, matching_chars);
        }

        free(first);
        free(second);
        free(matching_chars);
    }

    printf("Found matches: %s\n", found_matches);

    size_t matches_count = strlen(found_matches);
    size_t total_priority = 0;

    for (int i = 0; i < matches_count; i++) {
        size_t priority = get_pos_in_alphabet(found_matches[i]) + 1; // find position a-z = 1-26, A-Z = 27-52

        if (priority != 0) {
            total_priority += priority;
        } else {
            fprintf(stderr, "Error: %c not found in alphabet!\n", found_matches[i]);
        }
    }

    free(found_matches);

    printf("Total priority: %zu\n", total_priority);

    fclose(handle);
    return 0;
}
