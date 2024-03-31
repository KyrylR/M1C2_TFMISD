#include "math_functions.h"

// Recursive function as given in the pseudocode
double f(double x, double y) {
    if (x >= y) {
        return (x + y) / 2;
    } else {
        return f(f(x + 2, y - 1), f(x + 1, y - 2));
    }
}

double f_simple(double x, double y) {
    return (x + y) / 2;
}
