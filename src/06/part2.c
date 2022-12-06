#include <stdio.h>

enum bool_e {
    false,
    true
};

typedef enum bool_e bool_et;

bool_et char_in_array(unsigned char c, const unsigned char arr[], unsigned int n) {
    for (unsigned int i = 0; i < n; i++) {
        if (arr[i] == c) {
            return true;
        }
    }

    return false;
}

bool_et array_has_duplicates(const unsigned char arr[], unsigned int n) {
    for (unsigned int i = 0; i < n; i++) {
        if (char_in_array(arr[i], arr + i + 1, n - i - 1)) {
            return true;
        }
    }

    return false;
}

// i could do this cleverly, or i could be lazy
// guess which one i chose!!!

int main() {
    FILE *handle;

    handle = fopen("06.txt", "r");
    if (handle == NULL) {
        fputs("Error opening file", stderr);
        return 1;
    }

    unsigned char last_chars[13] = {0};

    // read file character by character until EOF
    int char_idx = 0;
    while (!feof(handle)) {
        char_idx++;

        unsigned char c = fgetc(handle);

        if (char_idx >= 13) {
            // if there are no repeats across the last 3 characters and this character
            if (!char_in_array(c, last_chars, 13) && !array_has_duplicates(last_chars, 13)) {
                printf("Final char: %c at index %d\n", c, char_idx);

                fclose(handle);

                return 0;
            }
        }

        // please refer to the comment near the top of this file

        // shift the last_chars array and add the new character
        last_chars[0] = last_chars[1];
        last_chars[1] = last_chars[2];
        last_chars[2] = last_chars[3];
        last_chars[3] = last_chars[4];
        last_chars[4] = last_chars[5];
        last_chars[5] = last_chars[6];
        last_chars[6] = last_chars[7];
        last_chars[7] = last_chars[8];
        last_chars[8] = last_chars[9];
        last_chars[9] = last_chars[10];
        last_chars[10] = last_chars[11];
        last_chars[11] = last_chars[12];
        last_chars[12] = c;
    }

    fclose(handle);

    fputs("Hit EOF before finding the marker!", stderr);

    return 1;
}