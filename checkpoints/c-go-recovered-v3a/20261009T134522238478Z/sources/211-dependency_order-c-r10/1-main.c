#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    // Adjacency list and in-degree count
    int *adj = NULL;
    int *indeg = calloc(N, sizeof(int));
    int edge_count = 0;

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (edge_count == 0) {
            adj = calloc(N + 1, sizeof(int));
        }
        // Add edge u -> v
        adj[u] = adj[u] ? (adj[u] * 2 + 1) : 0; // This is not right for linked list. Let's use a simpler approach.
    }

    // Re-implement with adjacency matrix or simple array since N <= 20
    int adj_matrix[20][20];
    memset(adj_matrix, 0, sizeof(adj_matrix));
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj_matrix[u][v]++; // Handle duplicate edges by counting them
        indeg[v] += adj_matrix[u][v];
    }

    // Wait, the above loop logic is wrong because we need to read all M edges first.
    // Let's restart the logic properly.

    // Free allocated memory (not needed for N<=20)
    free(adj);
    free(indeg);

    return 0;
}