#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#include "logical_eval.h"
#include "semantic_table.h"

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

// Function to preprocess and validate an expression
bool preprocessAndValidateExpression(const char *input, char *output) {
    int j = 0; // Index for output
    const int len = strlen(input);

    for (int i = 0; i < len; i++) {
        if (isspace(input[i])) {
            continue; // Skip whitespaces
        }

        // Validate character
        if (isOperator(input[i]) || isOperand(input[i])) {
            output[j++] = input[i];
        } else {
            printf("Invalid character found: %c\n", input[i]);
            return false; // Invalid character found
        }

        // Check for invalid sequences like "10" or "01"
        if (isOperand(input[i]) && i < len - 1) {
            if (isdigit(input[i + 1])) {
                printf("Invalid sequence found: %c%c\n", input[i], input[i + 1]);
                return false; // Invalid numeric sequence found
            }
        }
    }

    output[j] = '\0'; // Null-terminate the output string
    return true; // Validation successful
}
