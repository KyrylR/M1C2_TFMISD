#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/addition.h"

int main(int argc, char* argv[]) {
    if (argc != 4) {
        printf("Usage: %s x y c\n", argv[0]);
        return 1;
    }

    char* x = argv[1];
    char* y = argv[2];
    int c = atoi(argv[3]); // Base

    int n = strlen(x);
    int m = strlen(y);
    int common_length = (n > m) ? n + 1 : m + 1;

    x = padWithZeros(x, n, common_length);
    y = padWithZeros(y, m, common_length);

    char* result = add(x, y, c);

    printf("Result: %s\n", result);

    free(result); // Free the allocated memory
    free(x);      // Free the padded number
    free(y);      // Free the padded number

    return 0;
}
