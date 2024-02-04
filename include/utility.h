#ifndef UTILITY_H
#define UTILITY_H

#include <ctype.h>

// Convert a digit character to its integer value based on its representation and the base used.
// Supports alphanumeric characters, where '0'-'9' represent values 0-9 and 'a'-'z' (or 'A'-'Z') represent values 10-35.
int charToValue(const char ch);

// Convert an integer value to a character representation in a given base.
// Supports bases up to 36, where values 0-9 are represented by '0'-'9' and values 10-35 by 'a'-'z'.
char valueToChar(const int value);

#endif // UTILITY_H
