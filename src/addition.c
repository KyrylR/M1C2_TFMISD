#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "addition.h"

char* add(char* x, char* y, int c) {
    int n = strlen(x);

    char* result = (char*)malloc((n + 1) * sizeof(char)); // Allocate memory for the result
    memset(result, '0', (n + 1)); // Initialize result with '0's

    int b = 0; // current digit of the carry
    int i, j, k;

    for (i = n - 1, j = n - 1, k = n; i >= 0 || j >= 0; i--, j--, k--) {
        int xi = (i >= 0) ? ((isdigit(x[i])) ? (x[i] - '0') : (tolower(x[i]) - 'a' + 10)) : 0;
        int yi = (j >= 0) ? ((isdigit(y[j])) ? (y[j] - '0') : (tolower(y[j]) - 'a' + 10)) : 0;
        int sum = xi + yi + b;
        result[k] = (sum % c < 10) ? (sum % c + '0') : (sum % c - 10 + 'a'); // Convert integer to character
        b = sum / c;
    }

    return result;
}

char* padWithZeros(char* number, int length, int maxLength) {
    int numZeros = maxLength - length;
    char* paddedNumber = (char*)malloc((maxLength + 1) * sizeof(char)); // Allocate memory for the padded number
    memset(paddedNumber, '0', numZeros); // Initialize with leading zeros
    strcpy(paddedNumber + numZeros, number); // Copy the original number after leading zeros
    return paddedNumber;
}
