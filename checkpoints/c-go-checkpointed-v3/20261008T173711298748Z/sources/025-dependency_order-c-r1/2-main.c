#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    // Adjacency matrix for graph
    int adj[25][25];
    memset(adj, 0, sizeof(adj));
    
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (u >= N || v >= N) continue;
        adj[u][v] = 1;
    }

    // Compute in-degrees
    int *in_degree = (int *)calloc(N, sizeof(int));
    if (!in_degree) return 1;

    for (int u = 0; u < N; u++) {
        for (int v = 0; v < N; v++) {
            if (adj[u][v]) {
                in_degree[v]++;
            }
        }
    }

    // Kahn's algorithm with lexicographically smallest selection
    int *order = (int *)calloc(N, sizeof(int));
    int order_count = 0;
    int processed = 0;

    while (processed < N) {
        int best_node = -1;
        
        for (int i = 0; i < N; i++) {
            if (in_degree[i] == 0) {
                if (best_node == -1 || i < best_node) {
                    best_node = i;
                }
            }
        }

        if (best_node == -1) {
            printf("ERROR\n");
            free(in_degree);
            free(order);
            return 0;
        }

        order[order_count++] = best_node;
        in_degree[best_node] = -1; // Mark as processed
        processed++;

        for (int v = 0; v < N; v++) {
            if (adj[best_node][v]) {
                in_degree[v]--;
            }
        }
    }

    for (int i = 0; i < N; i++) {
        printf("%d%c", order[i], i == N - 1 ? '\n' : ' ');
    }

    free(in_degree);
    free(order);
    return 0;
}