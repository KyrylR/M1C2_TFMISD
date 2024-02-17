#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "utility.h"
#include "addition.h"

// Adds two numbers represented as strings in a given base and returns the result as a string
char *add(const char *x, const char *y, const int base) {
    const int len = strlen(x);
    char *result = (char *) malloc((len + 2) * sizeof(char)); // Allocate memory for the result + null terminator
    if (!result) return NULL; // Check for malloc failure

    result[len + 1] = '\0'; // Ensure the string is null-terminated
    int carry = 0;

    for (int i = len; i > 0; i--) {
        const int sum = charToValue(x[i - 1]) + charToValue(y[i - 1]) + carry;
        result[i] = (sum % base < 10) ? (sum % base + '0') : (sum % base - 10 + 'a');
        carry = sum / base;
    }
    result[0] = (carry < 10) ? (carry + '0') : (carry - 10 + 'a'); // Handle carry for the most significant digit

    // Find the first non-zero digit to truncate leading zeros
    int firstNonZero = 0;
    while (result[firstNonZero] == '0' && firstNonZero < len) {
        firstNonZero++;
    }
    if (firstNonZero == len + 1) { // All digits were zero
        char* zero = (char*)malloc(2);
        zero[0] = '0'; zero[1] = '\0';
        free(result);
        return zero;
    }

    char* finalResult = strdup(result + firstNonZero);
    free(result); // Free the initially allocated memory
    return finalResult;
}

// Pads the given string with zeros on the left to reach the desired maxLength
char *padWithZeros(const char *number, const int maxLength) {
    const int length = strlen(number);
    const int numZeros = maxLength - length;
    char *paddedNumber = (char *) malloc((maxLength + 1) * sizeof(char)); // +1 for null terminator
    if (!paddedNumber) return NULL; // Check for malloc failure

    memset(paddedNumber, '0', numZeros);
    strcpy(paddedNumber + numZeros, number);
    return paddedNumber;
}
