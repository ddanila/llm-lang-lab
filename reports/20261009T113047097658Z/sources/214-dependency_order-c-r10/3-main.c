#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    // Adjacency list: adj[u][v] = 1 means edge u -> v exists
    int adj[20][20];
    memset(adj, 0, sizeof(adj));

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (u >= 0 && u < N && v >= 0 && v < N) {
            adj[u][v] = 1;
        }
    }

    // Compute in-degrees
    int in_degree[20];
    memset(in_degree, 0, sizeof(in_degree));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (adj[i][j]) {
                in_degree[j]++;
            }
        }
    }

    // Kahn's algorithm with min-heap approach (scan for smallest index)
    int result[20];
    int count = 0;

    while (count < N) {
        int best_node = -1;

        // Find node with in_degree == 0 and smallest index among unprocessed nodes
        for (int i = 0; i < N; i++) {
            if (in_degree[i] == 0) {
                if (best_node == -1 || i < best_node) {
                    best_node = i;
                }
            }
        }

        if (best_node == -1) {
            // No node with in_degree 0, cycle exists
            printf("ERROR\n");
            return 0;
        }

        result[count++] = best_node;

        // Decrease in-degree of neighbors and mark processed node
        for (int i = 0; i < N; i++) {
            if (adj[best_node][i]) {
                in_degree[i]--;
            }
        }
        // Mark best_node as processed by setting its in_degree to -1
        in_degree[best_node] = -1;
    }

    // Output result
    for (int i = 0; i < N; i++) {
        printf("%d%c", result[i], (i == N - 1) ? '\n' : ' ');
    }

    return 0;
}