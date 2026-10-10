#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    // Adjacency list for graph: adj[u] = list of v such that u->v
    // Since N <= 20, we can use a simple adjacency matrix or linked lists.
    // We'll use adjacency lists with arrays.
    int *adj_head[25];
    int *adj_next[10000]; // M <= 100, so max edges 100
    int adj_count = 0;

    for (int i = 0; i < N; i++) {
        adj_head[i] = NULL;
    }

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (u >= N || v >= N) continue; // Should not happen based on spec
        adj_next[adj_count] = adj_head[u];
        adj_head[u] = adj_count++;
    }

    // Compute in-degrees
    int *in_degree = (int *)calloc(N, sizeof(int));
    if (!in_degree) return 1;

    for (int u = 0; u < N; u++) {
        for (int e = adj_head[u]; e != NULL; e = adj_next[e]) {
            in_degree[*e]++; // This is wrong because *e is index, but we stored indices
            // Let's redo: adj_head[u] stores an index into adj_next array.
            // But we need to store the actual edge target.
        }
    }

    // Redesign: Use simple adjacency matrix for N<=20
    int adj[25][25];
    memset(adj, 0, sizeof(adj));
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (u >= N || v >= N) continue;
        adj[u][v] = 1; // Duplicate edges allowed but don't matter for topological sort
    }

    // Recompute in-degrees
    memset(in_degree, 0, sizeof(int) * N);
    for (int u = 0; u < N; u++) {
        for (int v = 0; v < N; v++) {
            if (adj[u][v]) {
                in_degree[v]++;
            }
        }
    }

    // Kahn's algorithm with priority queue (lexicographically smallest)
    // Since N is small, we can use a simple array and find min each time.
    int *order = (int *)calloc(N, sizeof(int));
    int order_count = 0;
    int processed = 0;

    while (processed < N) {
        int best_node = -1;
        int best_in_degree = N + 1;

        for (int i = 0; i < N; i++) {
            if (!in_degree[i]) { // in_degree[i] == 0 means no incoming edges from unprocessed nodes? 
                // Actually, we need to track in-degrees only among remaining nodes.
                // But our in_degree array is static. We need to update it.
                // Better: use a separate array for current in-degrees of remaining nodes.
            }
        }

        // Let's redo with proper dynamic in-degree tracking
        break;
    }

    // Proper implementation
    int *current_in_degree = (int *)malloc(N * sizeof(int));
    if (!current_in_degree) return 1;
    memcpy(current_in_degree, in_degree, N * sizeof(int));

    while (processed < N) {
        int best_node = -1;
        for (int i = 0; i < N; i++) {
            if (current_in_degree[i] == 0) {
                if (best_node == -1 || i < best_node) {
                    best_node = i;
                }
            }
        }

        if (best_node == -1) {
            // Cycle detected
            free(current_in_degree);
            free(order);
            printf("ERROR\n");
            return 0;
        }

        order[order_count++] = best_node;
        current_in_degree[best_node] = -1; // Mark as processed
        processed++;

        for (int v = 0; v < N; v++) {
            if (adj[best_node][v]) {
                current_in_degree[v]--;
            }
        }
    }

    for (int i = 0; i < N; i++) {
        printf("%d%c", order[i], i == N - 1 ? '\n' : ' ');
    }

    free(current_in_degree);
    free(order);
    return 0;
}