#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    // Handle empty case
    if (N == 0 && M == 0) {
        printf("\n");
        return 0;
    }

    // Adjacency list: adj[u] -> array of v with count stored separately
    int **adj = malloc(N * sizeof(int*));
    int *adj_count = calloc(N, sizeof(int));
    
    for (int i = 0; i < N; i++) {
        adj[i] = malloc(16 * sizeof(int));
    }

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        // Add edge u -> v
        if (adj_count[u] >= 16) {
            int new_cap = 32;
            int *new_adj = realloc(adj[u], new_cap * sizeof(int));
            adj[u] = new_adj;
        }
        adj[u][adj_count[u]++] = v;
    }

    // Compute in-degrees
    int *in_degree = calloc(N, sizeof(int));
    for (int u = 0; u < N; u++) {
        if (adj[u]) {
            for (int i = 0; i < adj_count[u]; i++) {
                in_degree[adj[u][i]]++;
            }
        }
    }

    // Kahn's algorithm with min-heap using array and bubble sort for small N
    int *result = malloc(N * sizeof(int));
    int result_count = 0;

    // Find all nodes with in-degree 0
    int zero_nodes[25];
    int zero_count = 0;

    for (int i = 0; i < N; i++) {
        if (in_degree[i] == 0) {
            zero_nodes[zero_count++] = i;
        }
    }

    while (result_count < N && zero_count > 0) {
        // Sort zero_nodes to pick smallest first (bubble sort for simplicity)
        for (int i = 0; i < zero_count - 1; i++) {
            for (int j = i + 1; j < zero_count; j++) {
                if (zero_nodes[j] < zero_nodes[i]) {
                    int tmp = zero_nodes[i];
                    zero_nodes[i] = zero_nodes[j];
                    zero_nodes[j] = tmp;
                }
            }
        }

        // Pick smallest
        int u = zero_nodes[0];
        result[result_count++] = u;

        // Remove u from zero_nodes (shift elements)
        for (int i = 1; i < zero_count; i++) {
            zero_nodes[i - 1] = zero_nodes[i];
        }
        zero_count--;

        // Process neighbors of u
        if (adj[u]) {
            for (int i = 0; i < adj_count[u]; i++) {
                int v = adj[u][i];
                in_degree[v]--;
                if (in_degree[v] == 0) {
                    zero_nodes[zero_count++] = v;
                }
            }
        }
    }

    // Check if all nodes included
    if (result_count < N) {
        printf("ERROR\n");
    } else {
        for (int i = 0; i < N; i++) {
            printf("%d%c", result[i], (i == N - 1 ? '\n' : ' '));
        }
    }

    free(adj);
    free(adj_count);
    free(in_degree);
    free(result);
    return 0;
}