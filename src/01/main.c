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

    fread(buffer, 1, length, handle);
    fclose(handle);

    buffer[length] = '\0';

    printf("%s", buffer);
    return 0;
}
