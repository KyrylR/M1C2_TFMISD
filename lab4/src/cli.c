#include <stdio.h>
#include <stdlib.h>

#include "catalan.h"

void runCLI() {
    int n;
    printf("Enter the number of Catalan numbers to generate: ");
    scanf("%d", &n);

    int verbose;
    printf("Do you want to print the numbers? (0/1): ");
    scanf("%d", &verbose);

    if (verbose != 0 && verbose != 1) {
        printf("Please enter 0 or 1.\n");

        exit(1);
    }

    // Check for valid input
    if (n < 0) {
        printf("Please enter a non-negative integer.\n");
    } else {
        benchmarkCatalan(n, verbose);
    }

    while ((getchar()) != '\n') {}

    printf("Press Enter key to exit...\n");
    getchar(); // Wait for Enter key
}
