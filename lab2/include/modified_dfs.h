// modified_dfs.h
#ifndef MODIFIED_DFS_H
#define MODIFIED_DFS_H

#define MAX_VERTICES 100

extern int graph[MAX_VERTICES][MAX_VERTICES];
extern int V; // Number of vertices
extern int longestPath[MAX_VERTICES]; // To store the longest path
extern int longestPathLength; // Length of the longest path
extern int max_length; // Maximum length of the path not exceeding k

void DFS_LongestPath(int k);

#endif // MODIFIED_DFS_H
