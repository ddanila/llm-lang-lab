#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    // For N <= 20, use adjacency matrix
    int adj[20][20];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            adj[i][j] = 0;
        }
    }

    // Read M edges
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (u >= 0 && u < N && v >= 0 && v < N) {
            adj[u][v] = 1;
        }
    }

    // Compute in-degrees
    int *in_degree = malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        in_degree[i] = 0;
        for (int j = 0; j < N; j++) {
            if (adj[j][i]) {
                in_degree[i]++;
            }
        }
    }

    // Kahn's algorithm with min-heap simulation using array
    // We need to find nodes with in-degree 0, pick smallest index each time
    int result[20];
    int result_count = 0;

    for (int step = 0; step < N && result_count < N; step++) {
        // Find node with in-degree 0 and smallest index
        int best_node = -1;
        for (int i = 0; i < N; i++) {
            if (in_degree[i] == 0) {
                best_node = i;
                break;
            }
        }

        if (best_node == -1) {
            // Cycle detected
            printf("ERROR\n");
            free(in_degree);
            return 0;
        }

        result[result_count++] = best_node;

        // Decrease in-degree of neighbors
        for (int i = 0; i < N; i++) {
            if (adj[best_node][i]) {
                in_degree[i]--;
            }
        }
    }

    // Check if all nodes were ordered
    if (result_count != N) {
        printf("ERROR\n");
        free(in_degree);
        return 0;
    }

    // Output result
    for (int i = 0; i < N; i++) {
        printf("%d%c", result[i], (i == N - 1 ? '\n' : ' '));
    }

    free(in_degree);
    return 0;
}