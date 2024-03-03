#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "logical_eval.h"

int countUniqueVariables(const char *expression, char **varsArray) {
    bool varsPresent[26] = {false};
    int uniqueVarsCount = 0;
    *varsArray = NULL; // Start with a NULL pointer

    // Iterate through each character in the expression
    for (int i = 0; expression[i] != '\0'; i++) {
        char ch = expression[i];
        // Check if the character is a lowercase letter
        if (ch >= 'a' && ch <= 'z') {
            // Convert the letter to an index (e.g., 'a' -> 0, 'b' -> 1, ..., 'z' -> 25)
            int index = ch - 'a';
            // Check if we haven't seen this variable before
            if (!varsPresent[index]) {
                varsPresent[index] = true; // Mark this variable as seen
                uniqueVarsCount++; // Increment the count of unique variables

                // Resize the varsArray to accommodate the new variable
                *varsArray = realloc(*varsArray, uniqueVarsCount * sizeof(char));
                if (*varsArray == NULL) {
                    printf("Memory allocation failed\n");
                    exit(1); // Exit if memory allocation fails
                }
                (*varsArray)[uniqueVarsCount - 1] = ch; // Add the new variable to the array
            }
        }
    }

    return uniqueVarsCount; // Return the total count of unique variables
}

void buildTruthTable(const char* templateExpr) {
    char *varsArray;
    int numOfVars = countUniqueVariables(templateExpr, &varsArray); // Count the number of unique variables

    int totalCombinations = 1 << numOfVars; // 2^numOfVars combinations
    char expression[256]; // Buffer to hold each generated expression

    // Print table header
    for (int i = 0; i < numOfVars; i++) {
        printf("%c ", varsArray[i]);
    }
    printf("| %s\n", templateExpr);
    printf("--------------------------------\n");

    int semanticTable[NUM_OPERATIONS][NUM_VALUES][NUM_VALUES];
    fillSemanticTable(semanticTable);

    int currentVarRepresentation[26] = {0};
    int len = strlen(templateExpr);

    // Iterate over all possible combinations of variable truth values
    for (int num = 0; num < totalCombinations; num++) {

        for (int index = 0; index < numOfVars; index++) {
            currentVarRepresentation[varsArray[numOfVars - 1 - index] - 'a'] = (num >> index) & 1;
        }

        for (int i = 0; templateExpr[i] != '\0'; i++) {
            if (templateExpr[i] >= 'a' && templateExpr[i] <= 'z') {
                expression[i] = '0' + currentVarRepresentation[templateExpr[i] - 'a'];
            } else {
                expression[i] = templateExpr[i];
            }
        }

        expression[len] = '\0'; // Null-terminate the expression

        char preprocessedExpression[256]; // Buffer for the preprocessed expression

        // Preprocess and validate the original expression
        if (!preprocessAndValidateExpression(expression, preprocessedExpression)) {
            printf("Error: Invalid expression\n");
            return; // Exit if the expression is invalid
        }

        // Evaluate the generated expression and print the result
        bool result = evaluateExpression(preprocessedExpression, semanticTable);

        // Print the current combination and the result
        for (int i = numOfVars - 1; i >= 0; i--) {
            printf("%d ", (num >> i) & 1); // Print each variable's value in this combination
        }
        printf("| %d\n", result); // Print the evaluation result
    }
}

void runCLI() {
    char expression[256]; // Buffer for the expression

    printf("Enter the expression: ");
    fgets(expression, sizeof(expression), stdin); // Read a line from standard input

    // Remove the newline character if fgets() read one
    size_t len = strlen(expression);
    if (len > 0 && expression[len - 1] == '\n') {
        expression[len - 1] = '\0';
    }

    buildTruthTable(expression); // Pass the read expression for processing

    // No need to manually flush the buffer here since fgets() reads until newline

    printf("Press Enter key to exit...\n");
    getchar(); // Wait for Enter key
}
