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

char *find_matching_chars_threes(const char *str1, const char *str2, const char *str3) {
    size_t str1_len = strlen(str1);
    size_t str2_len = strlen(str2);
    size_t str3_len = strlen(str3);

    int occurences1[CHAR_MAX] = {0};
    int occurences2[CHAR_MAX] = {0};
    int occurences3[CHAR_MAX] = {0};

    for (int i = 0; i < str1_len; i++) {
        occurences1[str1[i]]++;
    }

    for (int i = 0; i < str2_len; i++) {
        occurences2[str2[i]]++;
    }

    for (int i = 0; i < str3_len; i++) {
        occurences3[str3[i]]++;
    }

    char *matching_chars = malloc((CHAR_MAX + 1) * sizeof(char));
    int matching_chars_index = 0;

    for (char i = 0; i < CHAR_MAX; i++) {
        if (occurences1[i] > 0 && occurences2[i] > 0 && occurences3[i] > 0) {
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

    char *found_matches = malloc((FILE_LEN + 1) * sizeof(char));
    strcpy(found_matches, "");

    char *bag1 = malloc(MAX_LEN * sizeof(char));
    char *bag2 = malloc(MAX_LEN * sizeof(char));
    char *bag3 = malloc(MAX_LEN * sizeof(char));

    // read the file line by line
    char buffer[MAX_LEN];
    size_t line_index = 0;
    while (fgets(buffer, MAX_LEN, handle) != NULL) {
        line_index++;

        // remove the newline character
        buffer[strcspn(buffer, "\n")] = 0;

        // copy the line to the bag
        if (line_index % 3 == 1) {
            strcpy(bag1, buffer);
        } else if (line_index % 3 == 2) {
            strcpy(bag2, buffer);
        } else if (line_index % 3 == 0) {
            strcpy(bag3, buffer);
        }

        // check if this is every third line
        if (line_index % 3 == 0) {
            // find the matching chars
            char *matching_chars = find_matching_chars_threes(bag1, bag2, bag3);

            // add to the found_matches array
            if (strcmp(found_matches, "") == 0) {
                strcpy(found_matches, matching_chars);
            } else {
                strcat(found_matches, matching_chars);
            }

            // reset the bags
            strcpy(bag1, "");
            strcpy(bag2, "");
            strcpy(bag3, "");

            free(matching_chars);
        }
    }
    
    fclose(handle);

    free(bag1);
    free(bag2);
    free(bag3);

    printf("Found matches: %s\n", found_matches);

    size_t matches_count = strlen(found_matches);
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

    free(found_matches);

    printf("Total priority: %zu\n", total_priority);
    return 0;
}
