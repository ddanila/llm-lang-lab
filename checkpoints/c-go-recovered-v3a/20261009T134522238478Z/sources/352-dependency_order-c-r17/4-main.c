#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    // Adjacency matrix for simplicity (N <= 20)
    int adj[20][20];
    int in_degree[20];
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            adj[i][j] = 0;
        }
        in_degree[i] = 0;
    }
    
    // Read M edges
    for (int k = 0; k < M; k++) {
        int u, v;
        scanf("%d %d", &u, &v);
        
        // Add edge u -> v
        if (adj[u][v] == 0) {
            adj[u][v] = 1;
            in_degree[v]++;
        }
    }

    // Kahn's algorithm: always pick smallest available node
    int result[20];
    int result_count = 0;
    
    for (int step = 0; step < N && result_count < N; step++) {
        // Find the smallest node with in-degree 0
        int best = -1;
        for (int i = 0; i < N; i++) {
            if (in_degree[i] == 0) {
                if (best == -1 || i < best) {
                    best = i;
                }
            }
        }
        
        if (best == -1) {
            // Cycle detected
            printf("ERROR\n");
            return 0;
        }
        
        result[result_count++] = best;
        
        // Decrement in-degree of neighbors
        for (int v = 0; v < N; v++) {
            if (adj[best][v]) {
                in_degree[v]--;
            }
        }
    }
    
    // Check for cycle
    if (result_count < N) {
        printf("ERROR\n");
    } else {
        for (int i = 0; i < N; i++) {
            printf("%d%c", result[i], i == N - 1 ? '\n' : ' ');
        }
    }
    
    return 0;
}