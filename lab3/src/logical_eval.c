// Add to semantic_table.c
#include "logical_eval.h"

#include <string.h> // For strchr()
#include <stdbool.h> // For bool type
#include <stdio.h>
#include <stdlib.h>

#include "semantic_table.h"

// Helper function to find operator index in the operations array
int findOperationIndex(char op) {
    switch (op) {
        case '&': return 1; // AND
        case '|': return 2; // OR
        case '^': return 3; // XOR
        case '>': return 4; // IMPLICATION (assuming -> is represented by > for simplicity)
        default: return -1;
    }
}

// Check if a character is an operand
bool isOperand(const char ch) {
    return ch == '0' || ch == '1';
}

// Check if a character is an operator
bool isOperator(const char ch) {
    return ch == '&' || ch == '|' || ch == '!' || ch == '^' || ch == '>';
}

// Utility function implementations (simplified)
int getPrecedence(char op) {
    // Function that defines operator precedence
    switch (op) {
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

// Convert infix expression to Polish (prefix) notation
void infixToPrefix(const char* infix, char* prefix) {
    int length = strlen(infix);
    char stack[length]; // Stack for operators
    int top = -1; // Top of the stack
    int j = 0; // Index for prefix array

    // Start from the right of the infix expression
    for (int i = length - 1; i >= 0; i--) {
        if (isOperand(infix[i])) {
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

bool evaluateExpression(const char *expression, int semanticTable[NUM_OPERATIONS][NUM_VALUES][NUM_VALUES]) {
    char prefix[256]; // Buffer for the prefix expression
    infixToPrefix(expression, prefix); // Convert the expression to prefix notation

    int len = strlen(prefix);
    char stack[len]; // Stack for storing expression elements during evaluation
    int top = -1; // Stack top index

    // Iterate through the expression from right to left
    for (int i = 0; i < len; i++) {
        const char ch = prefix[i];

        if (isOperand(ch)) {
            stack[++top] = ch; // Push operand onto stack
        } else if (isOperator(ch)) {
            // Check if there are enough operands on the stack for the operator
            if ((ch != '!' && top < 1) || (ch == '!' && top < 0)) { // '!' is unary, others are binary
                printf("Error: Insufficient operands\n");
                exit(1);
            }

            // Pop operand(s) from stack and apply the operator
            int opIndex = findOperationIndex(ch);
            if (opIndex == -1) {
                printf("Error: Invalid operator\n");
                exit(1);
            }

            bool operand1 = top > 0 ? stack[top--] - '0' : false; // Only get operand1 if not unary
            bool operand2 = stack[top] - '0'; // This could be the only operand for unary operators
            bool result;

            // Apply the operation
            if (ch == '!') { // Special handling for unary NOT operator
                result = semanticTable[opIndex][0][operand2];
            } else { // Binary operators
                result = semanticTable[opIndex][operand1][operand2];
            }

            // Push the result back onto the stack
            stack[top] = '0' + result;
        } else if (ch != '(' && ch != ')') { // Skip parentheses for prefix notation, add error handling for unexpected characters
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


