#include <stdio.h>

void runCLI() {
    while ((getchar()) != '\n') {}

    printf("Press Enter key to exit...\n");
    getchar(); // Wait for Enter key
}
