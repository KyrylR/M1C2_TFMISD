#include <gmp.h>
#include <time.h>
#include <stdio.h>

#include "catalan.h"

void printCatalanNumbers(const int n, const bool verbose) {
    mpz_t catalan[n+1]; // Array of big integers

    // Initialize the first Catalan number to 1
    mpz_init_set_ui(catalan[0], 1);

    if (verbose) gmp_printf("Catalan[0] = %Zd\n", catalan[0]);

    // Calculate and print the next n Catalan numbers
    for (int i = 1; i <= n; i++) {
        mpz_init(catalan[i]); // Initialize the next big integer
        for (int j = 0; j < i; j++) {
            mpz_t temp;
            mpz_init(temp);
            mpz_mul(temp, catalan[j], catalan[i - j - 1]);
            mpz_add(catalan[i], catalan[i], temp);
            mpz_clear(temp); // Clear the temporary variable to prevent memory leak
        }

        if (verbose) gmp_printf("Catalan[%d] = %Zd\n", i, catalan[i]);
    }

    // Clear all big integers after use
    for (int i = 0; i <= n; i++) {
        mpz_clear(catalan[i]);
    }
}

void benchmarkCatalan(const int n, bool verbose) {
    const clock_t start = clock(); // Record the start time
    printCatalanNumbers(n, verbose); // This is the function you want to benchmark
    const clock_t end = clock(); // Record the end time

    const double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC; // Compute the elapsed time

    printf("Time taken to generate %d Catalan numbers: %f seconds\n", n, cpu_time_used);
}

