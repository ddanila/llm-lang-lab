#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 20
#define MAXM 100

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) {
        return 0;
    }

    // Adjacency list for graph
    int adj[MAXN][MAXM];
    int in_degree[MAXN] = {0};
    int edge_count[MAXN] = {0}; // To track actual edges used

    // Read M edges
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (u >= 0 && u < N && v >= 0 && v < N) {
            adj[u][edge_count[u]++] = v;
            in_degree[v]++;
        }
    }

    // Kahn's algorithm with priority queue simulation using a sorted array
    // We need lexicographically smallest ordering, so we always pick the smallest available node
    
    int available[MAXN];
    int available_count = 0;
    
    // Initialize available nodes (in_degree == 0)
    for (int i = 0; i < N; i++) {
        if (in_degree[i] == 0) {
            available[available_count++] = i;
        }
    }

    int result[MAXN];
    int result_count = 0;

    // Process nodes
    while (available_count > 0) {
        // Find the smallest node in available
        int min_idx = 0;
        for (int i = 1; i < available_count; i++) {
            if (available[i] < available[min_idx]) {
                min_idx = i;
            }
        }

        int u = available[min_idx];
        // Remove from available
        for (int i = min_idx; i < available_count - 1; i++) {
            available[i] = available[i + 1];
        }
        available_count--;

        result[result_count++] = u;

        // Decrease in_degree of neighbors
        for (int i = 0; i < edge_count[u]; i++) {
            int v = adj[u][i];
            if (--in_degree[v] == 0) {
                available[available_count++] = v;
            }
        }
    }

    // Check if we processed all nodes (cycle detection)
    if (result_count != N) {
        printf("ERROR\n");
    } else {
        for (int i = 0; i < N; i++) {
            printf("%d", result[i]);
            if (i < N - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }

    return 0;
}