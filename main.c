#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/addition.h"

int main() {
    char x[256]; // Buffer for first number
    char y[256]; // Buffer for second number
    int c;       // Base

    printf("Enter x: ");
    scanf("%s", x);
    printf("Enter y: ");
    scanf("%s", y);
    printf("Enter c (base): ");
    scanf("%d", &c);

    const int n = strlen(x);
    const int m = strlen(y);
    const int common_length = (n > m) ? n + 1 : m + 1;

    char* padded_x = padWithZeros(x, common_length);
    char* padded_y = padWithZeros(y, common_length);

    char* result = add(padded_x, padded_y, c);

    printf("Result: %s\n", result);

    free(result); // Free the allocated memory
    free(padded_x); // Free the padded number
    free(padded_y); // Free the padded number

    printf("Press any key to exit...\n");
    getchar(); // To catch the newline character
    getchar(); // Wait for any key

    return 0;
}
