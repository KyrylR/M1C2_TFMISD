#include <string.h>

#include "modified_dfs.h"


int graph[MAX_VERTICES][MAX_VERTICES];
int visited[MAX_VERTICES];
int max_length = 0;
int V; // Number of vertices
int longestPath[MAX_VERTICES]; // To store the longest path
int longestPathLength = 0; // Length of the longest path
int currentPath[MAX_VERTICES]; // To store the current path during DFS

static void DFS(int v, int length, int* max_length, int k, int pathIndex) {
    // Adjusted to consider path length as the number of edges, not vertices
    if (length >= k) return; // Stop if the path length meets or exceeds k

    currentPath[pathIndex] = v; // Add current vertex to path
    if (length > *max_length) {
        *max_length = length;
        longestPathLength = pathIndex + 1; // Update longest path length
        memcpy(longestPath, currentPath, sizeof(int) * (pathIndex + 1)); // Copy current path to longest path
    }

    visited[v] = 1;
    for (int u = 0; u < V; u++) {
        if (graph[v][u] && !visited[u]) {
            DFS(u, length + 1, max_length, k, pathIndex + 1);
        }
    }
    visited[v] = 0; // Backtrack
}

void DFS_LongestPath(const int k) {
    max_length = 0; // Reset max_length for each call
    memset(longestPath, -1, sizeof(longestPath)); // Reset longest path
    longestPathLength = 0; // Reset longest path length
    for (int v = 0; v < V; v++) {
        memset(visited, 0, sizeof(visited)); // Reset visited for each vertex
        DFS(v, 0, &max_length, k, 0);
    }
}
