#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "logical_eval.h"

int findOperationIndex(const char op) {
    switch (op) {
        case '!': return 0; // NOT
        case '&': return 1; // AND
        case '|': return 2; // OR
        case '^': return 3; // XOR
        case '>': return 4; // IMPLICATION (assuming -> is represented by > for simplicity)
        default: return -1;
    }
}

bool isOperand(const char ch) {
    return ch == '0' || ch == '1';
}

bool isOperator(const char ch) {
    return ch == '&' || ch == '|' || ch == '!' || ch == '^' || ch == '>';
}

int getPrecedence(const char op) {
    switch (op) {
        case '!': // NOT has the highest precedence
            return 4;
        case '&': // AND is next
            return 3;
        case '^': // XOR comes after AND
            return 2;
        case '|': // OR is after XOR
            return 1;
        case '>': // IMPLICATION has the lowest precedence among these operators
            return 0;
        default:
            return 0; // for '(' and ')'
    }
}

// Convert infix expression to prefix notation
void infixToPrefix(const char *infix, char *prefix) {
    const int length = strlen(infix);
    char stack[length * 3]; // Stack for operators
    int top = -1; // Top of the stack
    int j = 0; // Index for prefix array

    // Start from the right of the infix expression
    for (int i = length - 1; i >= 0; i--) {
        if (isalpha(infix[i])) {
            // If character is an operand, add it to the prefix string
            prefix[j++] = infix[i];
        } else if (infix[i] == ')') {
            // Push ')' to stack
            stack[++top] = infix[i];
        } else if (infix[i] == '(') {
            // Pop everything from the stack until ')' is encountered
            while (top != -1 && stack[top] != ')') {
                prefix[j++] = stack[top--];
            }
            top--; // Pop off the ')'
        } else if (isOperator(infix[i])) {
            // Pop all operators with greater or equal precedence
            while (top != -1 && getPrecedence(infix[i]) < getPrecedence(stack[top])) {
                prefix[j++] = stack[top--];
            }
            // Push the current operator onto the stack
            stack[++top] = infix[i];
        }
    }

    // Pop all remaining operators from the stack
    while (top != -1) {
        prefix[j++] = stack[top--];
    }

    // Null-terminate and reverse the prefix string
    prefix[j] = '\0';
}

int countUniqueVariables(const char *expression, char **varsArray) {
    bool varsPresent[26] = {false};
    int uniqueVarsCount = 0;
    *varsArray = NULL; // Start with a NULL pointer

    // Iterate through each character in the expression
    for (int i = 0; expression[i] != '\0'; i++) {
        const char ch = expression[i];
        // Check if the character is a lowercase letter
        if (ch >= 'a' && ch <= 'z') {
            // Convert the letter to an index (e.g., 'a' -> 0, 'b' -> 1, ..., 'z' -> 25)
            const int index = ch - 'a';
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

#define MAX_MODELS 20
#define MAX_MODEL_LENGTH 256

char** splitIntoModels(const char* prefixExpr, int* numModels, char* modelPointers[MAX_MODELS]) {
    const int len = strlen(prefixExpr);
    // !a & b > (a | c > d ^ f)
    // "fd^ca|>ba!&>"
    char models[MAX_MODELS][MAX_MODEL_LENGTH];
    int modelIndex = 0;
    int i = 0;

    while (i < len) {
        if (prefixExpr[i] == '!') {
            // Found a negation operator, treat it as one symbol with the next operand
            char* leftModel = modelPointers[modelIndex - 1];
            static char combinedModel[MAX_MODEL_LENGTH];
            sprintf(combinedModel, "%c%s",  prefixExpr[i], leftModel);
            strcpy(models[modelIndex - 1], combinedModel);
            i++;
        } else if (isalpha(prefixExpr[i])) {
            // Found an operand, add it as a model
            sprintf(models[modelIndex], "%c", prefixExpr[i]);
            modelPointers[modelIndex] = models[modelIndex];
            modelIndex++;
            i++;
        } else {
            // Found an operator, combine the previous two models
            char* rightModel = modelPointers[modelIndex - 2];
            char* leftModel = modelPointers[modelIndex - 1];
            char combinedModel[MAX_MODEL_LENGTH];
            sprintf(combinedModel, "%s %c %s", leftModel, prefixExpr[i], rightModel);

            const int leftLen = strlen(leftModel);
            const int rightLen = strlen(rightModel);

            if (leftLen <= 2 && rightLen <= 2) {
                modelIndex -= 2;
            }

            strcpy(models[modelIndex], combinedModel);
            modelPointers[modelIndex] = models[modelIndex];
            modelIndex++;
            i++;
        }
    }

    *numModels = modelIndex;
}

void sortModelPointers(char *modelPointers[], int numModels) {
    for (int i = 0; i < numModels - 1; i++) {
        for (int j = 0; j < numModels - i - 1; j++) {
            if (strlen(modelPointers[j]) > strlen(modelPointers[j + 1])) {
                // Swap modelPointers[j] and modelPointers[j+1]
                char *temp = modelPointers[j];
                modelPointers[j] = modelPointers[j + 1];
                modelPointers[j + 1] = temp;
            }
        }
    }
}

void sortStringAlphabetically(char *varsArray) {
    int n = strlen(varsArray);
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (varsArray[i] > varsArray[j]) {
                char temp = varsArray[i];
                varsArray[i] = varsArray[j];
                varsArray[j] = temp;
            }
        }
    }
}

void buildTruthTable(const char *templateExpr) {
    char *varsArray;
    const int numOfVars = countUniqueVariables(templateExpr, &varsArray); // Count the number of unique variables

    sortStringAlphabetically(varsArray);

    const int totalCombinations = 1 << numOfVars; // 2^numOfVars combinations
    char expression[256]; // Buffer to hold each generated expression

    char prefix[256]; // Buffer for the prefix expression
    infixToPrefix(templateExpr, prefix); // Convert the expression to prefix notation

    int numModels;
    char *modelPointers[MAX_MODELS];
    splitIntoModels(prefix, &numModels, modelPointers);

    sortModelPointers(modelPointers, numModels);

    // Print table header
    for (int i = 0; i < numOfVars; i++) {
        printf("%c ", varsArray[i]);
    }

    int maxModelLength = strlen(templateExpr);

    for (int i = 0; i < numModels - 1; i++) {
        printf("¦ %-*s ", maxModelLength, modelPointers[i]);
    }

    printf("¦ %s\n", templateExpr);

    // Print separator line
    for (int i = 0; i < numOfVars; i++) {
        printf("--");
    }

    for (int i = 0; i < numModels; i++) {
        printf("¦%.*s", maxModelLength + 2, "-------------------------------------");
    }

    printf("\n");

    int currentVarRepresentation[26] = {0};
    const int len = strlen(prefix);

    // Iterate over all possible combinations of variable truth values
    for (int num = 0; num < totalCombinations; num++) {
        for (int index = 0; index < numOfVars; index++) {
            currentVarRepresentation[varsArray[numOfVars - 1 - index] - 'a'] = (num >> index) & 1;
        }

        // Evaluate each model and store the results
        int modelResults[MAX_MODELS];
        for (int i = 0; i < numModels - 1; i++) {
            char modelPrefix[256];
            infixToPrefix(modelPointers[i], modelPrefix);

            const int modelPrefixLen = strlen(modelPrefix);
            for (int j = 0; j < modelPrefixLen; j++) {
                if (modelPrefix[j] >= 'a' && modelPrefix[j] <= 'z') {
                    expression[j] = '0' + currentVarRepresentation[modelPrefix[j] - 'a'];
                } else {
                    expression[j] = modelPrefix[j];
                }
            }
            expression[modelPrefixLen] = '\0'; // Null-terminate the expression

            modelResults[i] = evaluateExpression(expression);
        }

        // Print the current combination and the model results
        for (int i = numOfVars - 1; i >= 0; i--) {
            printf("%d ", (num >> i) & 1); // Print each variable's value in this combination
        }

        for (int i = 0; i < numModels - 1; i++) {
            printf("¦ %-*d ", maxModelLength, modelResults[i]);
        }

        for (int i = 0; prefix[i] != '\0'; i++) {
            if (prefix[i] >= 'a' && prefix[i] <= 'z') {
                expression[i] = '0' + currentVarRepresentation[prefix[i] - 'a'];
            } else {
                expression[i] = prefix[i];
            }
        }

        expression[len] = '\0'; // Null-terminate the expression

        // Evaluate the generated expression and print the result
        const bool result = evaluateExpression(expression);
        printf("¦ %d\n", result); // Print the evaluation result
    }
}

bool evaluateExpression(const char *expression) {
    const int len = strlen(expression);
    char stack[len * 3]; // Stack for storing expression elements during evaluation
    int top = -1; // Stack top index

    for (int i = 0; i < len; i++) {
        const char ch = expression[i];

        if (isOperand(ch)) {
            stack[++top] = ch; // Push operand onto stack
        } else if (isOperator(ch)) {
            // Check if there are enough operands on the stack for the operator
            if ((ch != '!' && top < 1) || (ch == '!' && top < 0)) {
                // '!' is unary, others are binary
                printf("Error: Insufficient operands\n");
                exit(1);
            }

            // Pop operand(s) from stack and apply the operator
            const int opIndex = findOperationIndex(ch);
            if (opIndex == -1) {
                printf("Error: Invalid operator\n");
                exit(1);
            }

            bool result;

            // Apply the operation
            if (ch == '!') {
                const bool operand2 = stack[top] - '0';

                // Special handling for unary NOT operator
                result = !operand2;
            } else {
                const bool operand1 = stack[top--] - '0';
                const bool operand2 = stack[top] - '0';

                // Binary operators
                switch (ch) {
                    case '&':
                        result = operand1 && operand2;
                        break;
                    case '|':
                        result = operand1 || operand2;
                        break;
                    case '^':
                        result = operand1 ^ operand2;
                        break;
                    case '>':
                        result = !operand1 || operand2;
                        break;
                    default:
                        printf("Error: Invalid operator\n");
                        exit(1);
                }
            }

            // Push the result back onto the stack
            stack[top] = '0' + result;
        } else if (ch != '(' && ch != ')') {
            // Skip parentheses for prefix notation, add error handling for unexpected characters
            printf("Error: Unexpected character '%c'\n", ch);
            exit(1);
        }
    }

    // Final result should be at the top of the stack
    if (top != 0) {
        printf("Error: Unresolved expression\n");
        exit(1);
    }

    return stack[top] == '1';
}
