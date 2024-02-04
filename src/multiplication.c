#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utility.h"
#include "multiplication.h"


char* multiply(const char* x, const char* y, const int base) {
    const int n = strlen(x);
    const int t = strlen(y);
    const int resultSize = n + t + 1; // +1 for extra carry, +1 for null-terminator
    char* result = (char*)calloc(resultSize, sizeof(char)); // Initialize with zeros

    if (!result) return NULL; // Allocation check

    for (int i = 0; i < resultSize - 1; i++) {
        result[i] = '0';
    }

    for (int i = t - 1; i >= 0; i--) {
        int carry = 0;
        for (int j = n - 1; j >= 0; j--) {
            const int product = charToValue(x[j]) * charToValue(y[i]) + charToValue(result[i + j + 1]) + carry;
            result[i + j + 1] = valueToChar(product % base);
            carry = product / base;
        }
        result[i] = valueToChar(carry);
    }

    // Remove leading zeros from the result
    int start = 0;
    while (start < resultSize - 2 && result[start] == '0') {
        start++;
    }

    char* finalResult = strdup(result + start);

    free(result);

    return finalResult;
}
