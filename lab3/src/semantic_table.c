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
