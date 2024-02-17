#include <stdio.h>
#include <stdlib.h>
#include "utility.h" // Assuming utility.h contains charToValue and valueToChar functions

// Function to convert integer n to its representation in base c
char* imag(const int n, const int c) {
    char* result = (char*)malloc(65); // Assuming the result won't be longer than 64 digits + null terminator
    if (!result) return NULL; // Check for malloc failure

    int i = 0;
    int x = n;
    int q = x / c;
    result[i++] = valueToChar(x - q * c);

    while (q > 0) {
        x = q;
        q = x / c;
        result[i++] = valueToChar(x - q * c);
    }

    result[i] = '\0'; // Null-terminate the string

    // Reverse the string since the algorithm produces digits in reverse order
    for (int j = 0; j < i / 2; j++) {
        char temp = result[j];
        result[j] = result[i - j - 1];
        result[i - j - 1] = temp;
    }

    return result;
}
