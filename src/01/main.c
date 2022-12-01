#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE* handle;
    char* buffer;

    handle = fopen("01.txt", "r");
    if (handle == NULL) {
        printf("Error opening file");
        return 1;
    }

    fseek(handle, 0, SEEK_END);
    size_t length = ftell(handle);
    fseek(handle, 0, SEEK_SET);

    buffer = malloc(length + 1);

    if (buffer == NULL) {
        printf("Error allocating memory");
        return 1;
    }

    // reading line by line would actually simplify this a lot
    // then i can just strtol or check for empty line
    fread(buffer, 1, length, handle); // could read line-by-line, but this is easier
    fclose(handle);

    buffer[length] = '\0';

    int current_calories = 0;
    int total_calories = 0;
    int record_calories = 0;

    for (int i = 0; i < length; i++) {
        if (buffer[i] == '\n') {
            if (total_calories > record_calories) {
                record_calories = total_calories;
            }
            total_calories = 0;
        }
    }
    return 0;
}
