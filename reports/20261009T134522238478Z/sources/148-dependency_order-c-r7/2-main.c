#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) {
        return 0;
    }

    // For N=0, output empty line
    if (N == 0) {
        printf("\n");
        return 0;
    }

    // Use dynamic arrays for adjacency list
    int **adj = malloc(N * sizeof(int*));
    int *edge_count = calloc(N, sizeof(int));
    int *in_deg = calloc(N, sizeof(int));
    
    for (int i = 0; i < N; i++) {
        adj[i] = NULL;
        edge_count[i] = 0;
        in_deg[i] = 0;
    }

    // Read M edges
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (u >= 0 && u < N && v >= 0 && v < N) {
            // Add edge u -> v
            edge_count[u]++;
            int *tmp = adj[u];
            int new_size = edge_count[u];
            adj[u] = malloc(new_size * sizeof(int));
            if (tmp) {
                for (int j = 0; j < edge_count[u] - 1; j++) {
                    adj[u][j] = tmp[j];
                }
            }
            adj[u][edge_count[u] - 1] = v;
        }
    }

    // Compute in-degrees
    for (int u = 0; u < N; u++) {
        for (int j = 0; j < edge_count[u]; j++) {
            int v = adj[u][j];
            if (v >= 0 && v < N) {
                in_deg[v]++;
            }
        }
    }

    // Kahn's algorithm - use a sorted available list
    int *available = malloc(N * sizeof(int));
    int avail_count = 0;
    for (int i = 0; i < N; i++) {
        if (in_deg[i] == 0) {
            available[avail_count++] = i;
        }
    }

    int *result = malloc(N * sizeof(int));
    int result_count = 0;

    while (avail_count > 0) {
        // Find the smallest node in available (linear scan, N <= 20)
        int min_idx = 0;
        for (int i = 1; i < avail_count; i++) {
            if (available[i] < available[min_idx]) {
                min_idx = i;
            }
        }
        int u = available[min_idx];
        result[result_count++] = u;

        // Remove u from available by shifting
        for (int i = min_idx; i < avail_count - 1; i++) {
            available[i] = available[i + 1];
        }
        avail_count--;

        // Decrease in-degrees of neighbors and add new available nodes
        for (int j = 0; j < edge_count[u]; j++) {
            int v = adj[u][j];
            if (v >= 0 && v < N) {
                in_deg[v]--;
                if (in_deg[v] == 0) {
                    available[avail_count++] = v;
                }
            }
        }
    }

    // Check if all nodes are included (cycle detection)
    if (result_count != N) {
        printf("ERROR\n");
    } else {
        for (int i = 0; i < N; i++) {
            printf("%d%c", result[i], i == N - 1 ? '\n' : ' ');
        }
    }

    free(in_deg);
    free(available);
    free(result);
    for (int i = 0; i < N; i++) {
        if (adj[i]) free(adj[i]);
    }
    free(adj);
    free(edge_count);

    return 0;
}