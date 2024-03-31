#include <stdio.h>
#include <string.h>
#include <time.h>

#include "math_functions.h"

void runCLI() {
    double x, y, result;
    char choice[10];
    clock_t start, end;
    double cpu_time_used;

    // Main loop
    while (1) {
        printf("Enter 'f' for recursive or 'simple' for simplified function (or type 'exit' to quit): ");
        scanf("%9s", choice); // Read the choice

        if (strcmp(choice, "exit") == 0) {
            break; // Exit the loop and end the program
        }

        printf("Enter values for x and y separated by space: ");
        if (scanf("%lf %lf", &x, &y) == 2) {
            // Clear the input buffer
            while ((getchar()) != '\n') {}

            if (strcmp(choice, "f") == 0) {
                start = clock();
                // Call the recursive function f with input values
                result = f(x, y);
                end = clock();
            } else if (strcmp(choice, "simple") == 0) {
                start = clock();
                // Call the simplified function f_simple with input values
                result = f_simple(x, y);
                end = clock();
            } else {
                printf("Invalid function choice.\n");
                continue;
            }

            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            printf("Result of %s(%.2lf, %.2lf) = %.2lf\n", choice, x, y, result);
            printf("Time taken: %f seconds\n", cpu_time_used);
        } else {
            // Clear the input buffer
            while ((getchar()) != '\n') {}
            printf("Invalid input, please enter numbers for x and y.\n");
        }
    }

    printf("Exiting the program...\n");
}