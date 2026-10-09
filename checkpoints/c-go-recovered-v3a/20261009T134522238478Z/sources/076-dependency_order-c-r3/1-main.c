#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    // Adjacency list for graph
    // adj[i] is a dynamic array of neighbors
    int *adj[20];
    int deg[20]; // in-degree
    int count[20]; // number of edges from each node

    for (int i = 0; i < N; i++) {
        adj[i] = NULL;
        count[i] = 0;
        deg[i] = 0;
    }

    for (int k = 0; k < M; k++) {
        int u, v;
        scanf("%d %d", &u, &v);
        // Allow self-loops and duplicate edges
        if (u >= N || v >= N) continue;
        
        // Add edge u -> v
        adj[u] = realloc(adj[u], (count[u] + 1) * sizeof(int));
        if (!adj[u]) {
            fprintf(stderr, "Memory allocation error\n");
            return 1;
        }
        adj[u][count[u]] = v;
        count[u]++;
        deg[v]++;
    }

    // Kahn's algorithm with a min-heap (priority queue) for lexicographically smallest order
    // Since N is small (<=20), we can use a simple selection approach
    
    int *result = malloc(N * sizeof(int));
    if (!result) {
        fprintf(stderr, "Memory allocation error\n");
        return 1;
    }

    int result_idx = 0;

    // Use a boolean array to track available nodes (in-degree == 0)
    int available[20];
    memset(available, 0, sizeof(available));

    for (int i = 0; i < N; i++) {
        if (deg[i] == 0) {
            available[i] = 1;
        }
    }

    // Repeatedly find the smallest available node and add to result
    while (result_idx < N) {
        int min_node = -1;
        int min_val = 21; // Larger than any possible node index
        
        for (int i = 0; i < N; i++) {
            if (available[i] && i < min_val) {
                min_val = i;
                min_node = i;
            }
        }

        if (min_node == -1) {
            // No node with in-degree 0, but we still need to output nodes
            // This means there's a cycle
            printf("ERROR\n");
            free(result);
            return 0;
        }

        result[result_idx++] = min_node;
        available[min_node] = 0;

        // Decrease in-degree of neighbors
        for (int i = 0; i < count[min_node]; i++) {
            int v = adj[min_node][i];
            deg[v]--;
            if (deg[v] == 0) {
                available[v] = 1;
            }
        }
    }

    // Output result
    for (int i = 0; i < N; i++) {
        printf("%d", result[i]);
        if (i < N - 1) {
            printf(" ");
        }
    }
    printf("\n");

    free(result);
    return 0;
}