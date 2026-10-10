#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    // Adjacency list using linked lists for edges
    // adj[u] points to first edge from u
    int *adj = calloc(N, sizeof(int));
    int *next = malloc(M * sizeof(int));
    if (!adj || !next) { free(adj); free(next); return 1; }

    // Store edges in order of input to process them
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        next[i] = adj[u];
        adj[u] = i;
    }

    // Compute in-degrees
    int *in_degree = calloc(N, sizeof(int));
    for (int u = 0; u < N; u++) {
        for (int e = adj[u]; e != -1; e = next[e]) {
            int v = e + 1; // We'll compute v when processing edge list
        }
    }

    // Better: store edges in a flat array with target
    int *targets = malloc(M * sizeof(int));
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        targets[i] = v;
    }

    // Re-read N M and edges properly - need to store first
    // Let's restart with proper storage
    
    free(adj);
    free(next);
    free(in_degree);
    free(targets);
    
    adj = calloc(N, sizeof(int));
    next = malloc(M * sizeof(int));
    targets = malloc(M * sizeof(int));
    if (!adj || !next || !targets) { free(adj); free(next); free(targets); return 1; }

    // Reset adj to -1
    for (int i = 0; i < N; i++) adj[i] = -1;

    // Read edges again
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        targets[i] = v;
        next[i] = adj[u];
        adj[u] = i;
        in_degree[v]++;
    }

    // Kahn's algorithm with min-heap simulation using array and linear scan
    // Since N <= 20, we can use a simple array to find minimum in-degrees
    
    int *order = calloc(N, sizeof(int));
    int order_count = 0;
    
    int *in_deg = malloc(N * sizeof(int));
    memcpy(in_deg, in_degree, N * sizeof(int));

    // Use a priority queue simulated by scanning all nodes with in_deg == 0
    // To get lexicographically smallest, always pick the smallest index node
    
    while (order_count < N) {
        int best = -1;
        for (int i = 0; i < N; i++) {
            if (in_deg[i] == 0 && (best == -1 || i < best)) {
                best = i;
            }
        }
        
        if (best == -1) {
            // Cycle detected
            printf("ERROR\n");
            free(adj);
            free(next);
            free(targets);
            free(order);
            free(in_deg);
            return 0;
        }
        
        order[order_count++] = best;
        in_deg[best] = -1; // Mark as removed
        
        // Decrease in-degree of neighbors
        for (int e = adj[best]; e != -1; e = next[e]) {
            int v = targets[e];
            if (in_deg[v] > 0) {
                in_deg[v]--;
            }
        }
    }
    
    // Output result
    for (int i = 0; i < N; i++) {
        printf("%d", order[i]);
        if (i < N - 1) printf(" ");
    }
    printf("\n");

    free(adj);
    free(next);
    free(targets);
    free(order);
    free(in_deg);
    
    return 0;
}