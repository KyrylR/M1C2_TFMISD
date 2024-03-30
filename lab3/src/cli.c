#include <stdio.h>
#include <string.h>

#include "logical_eval.h"

void runCLI() {
    char expression[256]; // Buffer for the expression

    printf("Enter the expression using the operators: & (AND), | (OR), ! (NOT), ^ (XOR), > (IMPLICATION): ");
    fgets(expression, sizeof(expression), stdin); // Read a line from standard input

    // Remove the newline character if fgets() read one
    const size_t len = strlen(expression);
    if (len > 0 && expression[len - 1] == '\n') {
        expression[len - 1] = '\0';
    }

    buildTruthTable(expression); // Pass the read expression for processing

    printf("Press Enter key to exit...\n");
    getchar(); // Wait for Enter key
}
