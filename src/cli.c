#include <stdio.h>
#include <stdlib.h>

#include "cli.h"
#include "imag.h"
#include "addition.h"
#include "multiplication.h"

void runCLI() {
    char x[256] = {0}, y[256] = {0}; // Initialize to zeros
    int base, n;
    char operation;

    printf("Choose operation [a]ddition, [m]ultiplication, or [i]mag: ");
    scanf(" %c", &operation);

    // IMAG operation has different inputs, handle it separately
    if (operation == 'i' || operation == 'I') {
        printf("Enter n: ");
        scanf("%d", &n);
        printf("Enter base: ");
        scanf("%d", &base);
        char* imagResult = imag(n, base);
        printf("IMAG Result: %s\n", imagResult);
        free(imagResult);
    } else {
        // Handle addition and multiplication operations
        printf("Enter x: ");
        scanf("%s", x);
        printf("Enter y: ");
        scanf("%s", y);
        printf("Enter base: ");
        scanf("%d", &base);

        // Adjust the function call to match the correct parameters
        char* padded_x = padWithZeros(x, base); // Assuming base determines padding
        char* padded_y = padWithZeros(y, base); // Adjust if padWithZeros signature is different

        switch (operation) {
            case 'a':
            case 'A': {
                char* result = add(padded_x, padded_y, base);
                printf("Addition Result: %s\n", result);
                free(result);
                break;
            }
            case 'm':
            case 'M': {
                char* result = multiply(padded_x, padded_y, base);
                printf("Multiplication Result: %s\n", result);
                free(result);
                break;
            }
            default:
                printf("Invalid operation selected.\n");
        }

        free(padded_x);
        free(padded_y);
    }

    // Flush the input buffer
    while ((getchar()) != '\n') {}

    printf("Press Enter key to exit...\n");
    getchar(); // Wait for Enter key
}
