#include <stdio.h>

#include "modified_dfs.h"

void readGraphFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fscanf(file, "%d", &V); // Read number of vertices

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            fscanf(file, "%d", &graph[i][j]); // Read the adjacency matrix
        }
    }

    fclose(file);
}

void runCLI() {
    char choice;
    int k;

    printf("Do you want to input data manually or from a file? (m/f): ");
    scanf(" %c", &choice);

    if (choice == 'f' || choice == 'F') {
        char filename[256];
        printf("Enter filename: ");
        scanf("%s", filename);
        readGraphFromFile(filename);
    } else {
        printf("Enter the number of vertices in the graph: ");
        scanf("%d", &V);

        printf("Enter the adjacency matrix for the graph:\n");
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                scanf("%d", &graph[i][j]);
            }
        }
    }

    printf("Enter the maximum path length (k): ");
    scanf("%d", &k);

    DFS_LongestPath(k);

    printf("The longest path of length not exceeding %d has length %d: ", k, longestPathLength);
    for (int i = 0; i < longestPathLength; i++) {
        printf("%d ", longestPath[i]);
    }
    printf("\n");

    // Flush the input buffer
    while ((getchar()) != '\n') {}

    printf("Press Enter key to exit...\n");
    getchar(); // Wait for Enter key
}
