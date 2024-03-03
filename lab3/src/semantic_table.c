#include <stdio.h>

#include "semantic_table.h"

#include <ctype.h>
#include <stdbool.h>
#include <string.h>

// Function to fill the semantic table
void fillSemanticTable(int semanticTable[NUM_OPERATIONS][NUM_VALUES][NUM_VALUES]) {
    // Fill in the table for NOT operation (special case, unary operator)
    for (int i = 0; i < NUM_VALUES; i++) {
        semanticTable[0][i][0] = !i; // NOT operation only needs one operand
    }

    // Fill in the table for AND operation
    for (int i = 0; i < NUM_VALUES; i++) {
        for (int j = 0; j < NUM_VALUES; j++) {
            semanticTable[1][i][j] = i && j;
        }
    }

    // Fill in the table for OR operation
    for (int i = 0; i < NUM_VALUES; i++) {
        for (int j = 0; j < NUM_VALUES; j++) {
            semanticTable[2][i][j] = i || j;
        }
    }

    // Fill in the table for XOR operation
    for (int i = 0; i < NUM_VALUES; i++) {
        for (int j = 0; j < NUM_VALUES; j++) {
            semanticTable[3][i][j] = i ^ j;
        }
    }

    // Fill in the table for IMPLICATION operation
    for (int i = 0; i < NUM_VALUES; i++) {
        for (int j = 0; j < NUM_VALUES; j++) {
            semanticTable[4][i][j] = !i || j; // a → b is equivalent to ¬a ∨ b
        }
    }
}

// Function to print the semantic table for demonstration
void printSemanticTable(int semanticTable[NUM_OPERATIONS][NUM_VALUES][NUM_VALUES]) {
    char *operations[] = {"NOT", "AND", "OR", "XOR", "IMPLICATION"};
    for (int op = 0; op < NUM_OPERATIONS; op++) {
        printf("Operation: %s\n", operations[op]);
        for (int i = 0; i < NUM_VALUES; i++) {
            for (int j = 0; j < NUM_VALUES; j++) {
                // Note: For NOT operation, the second operand is irrelevant
                if (op == 0) { // Special case for unary NOT operation
                    printf("%d: %d\n", i, semanticTable[op][i][0]);
                    break; // Skip the inner loop for NOT
                } else {
                    printf("%d %s %d: %d\n", i, operations[op], j, semanticTable[op][i][j]);
                }
            }
        }
        printf("\n"); // Add a newline for better readability between operations
    }
}

// Function to preprocess and validate an expression
bool preprocessAndValidateExpression(const char *input, char *output) {
    int j = 0; // Index for output
    int len = strlen(input);

    for (int i = 0; i < len; i++) {
        if (isspace(input[i])) {
            continue; // Skip whitespaces
        }

        // Validate character
        if (input[i] == '0' || input[i] == '1' || input[i] == '(' || input[i] == ')' ||
            input[i] == '!' || input[i] == '&' || input[i] == '|' || input[i] == '^' || input[i] == '>') {
            output[j++] = input[i];
            } else {
                printf("Invalid character found: %c\n", input[i]);
                return false; // Invalid character found
            }

        // Check for invalid sequences like "10" or "01"
        if ((input[i] == '1' || input[i] == '0') && i < len - 1) {
            if (isdigit(input[i + 1])) {
                printf("Invalid sequence found: %c%c\n", input[i], input[i + 1]);
                return false; // Invalid numeric sequence found
            }
        }

        // if !number found replace with opposite number
        if (input[i] == '!') {
            if (input[i + 1] == '0') {
                output[j - 1] = '1';
            } else if (input[i + 1] == '1') {
                output[j - 1] = '0';
            }

            i++; // Skip the next character
        }
    }

    output[j] = '\0'; // Null-terminate the output string
    return true; // Validation successful
}

