#include <ctype.h>

// Helper function to convert a digit character to its integer value
int charToValue(const char ch) {
    if (isdigit(ch)) return ch - '0';
    if (isalpha(ch)) return tolower(ch) - 'a' + 10;
    return 0; // Non-alphanumeric characters treated as 0
}

// Helper function to convert an integer value to a digit character
char valueToChar(const int value) {
    if (value < 10) return '0' + value;
    return 'a' + (value - 10);
}
