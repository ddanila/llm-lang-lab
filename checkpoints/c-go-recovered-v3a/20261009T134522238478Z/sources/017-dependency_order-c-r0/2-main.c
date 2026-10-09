#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 21

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    if (N == 0 && M == 0) {
        printf("\n");
        return 0;
    }

    // Adjacency matrix to handle duplicate edges and self-loops properly
    int adj[MAX_NODES][MAX_NODES];
    memset(adj, 0, sizeof(adj));

    // in_degree for Kahn's algorithm
    int in_degree[MAX_NODES] = {0};

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        
        // Handle self-loops - they create cycles
        if (u == v) {
            // Self-loop detected, we'll mark it later
        } else {
            adj[u][v] = 1;
            in_degree[v]++;
        }
    }

    // Check for self-loops
    int has_self_loop = 0;
    for (int i = 0; i < N; i++) {
        if (adj[i][i]) {
            has_self_loop = 1;
            break;
        }
    }

    if (has_self_loop) {
        printf("ERROR\n");
        return 0;
    }

    // Kahn's algorithm with priority queue (lexicographically smallest)
    // Use a min-heap based on node index
    int order[MAX_NODES];
    int count = 0;

    // For lexicographically smallest, we need to process nodes in increasing order
    // among those with in_degree == 0
    
    while (count < N) {
        int best_node = -1;
        
        // Find the smallest node with in_degree == 0
        for (int i = 0; i < N; i++) {
            if (in_degree[i] == 0) {
                best_node = i;
                break;
            }
        }

        if (best_node == -1) {
            // No node with in_degree == 0, but we haven't processed all nodes
            // This means there's a cycle
            printf("ERROR\n");
            return 0;
        }

        order[count++] = best_node;
        in_degree[best_node] = -1; // Mark as processed
        
        // Decrease in_degree of neighbors
        for (int v = 0; v < N; v++) {
            if (adj[best_node][v]) {
                in_degree[v]--;
            }
        }
    }

    // Output the result
    for (int i = 0; i < count; i++) {
        printf("%d", order[i]);
        if (i < count - 1) printf(" ");
    }
    printf("\n");

    return 0;
}