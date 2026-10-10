#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    // For N <= 20, we can use an adjacency matrix and handle duplicate edges by counting
    int adj[20][20];
    memset(adj, 0, sizeof(adj));
    int indeg[20] = {0};
    
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (u >= 0 && u < N && v >= 0 && v < N) {
            adj[u][v]++;
            indeg[v]++; // Each edge from u to v increases indegree of v by 1
        }
    }

    int result[20];
    int result_count = 0;
    
    for (int step = 0; step < N; step++) {
        int best_node = -1;
        
        // Find the lexicographically smallest node with indegree 0
        for (int i = 0; i < N; i++) {
            if (indeg[i] == 0) {
                if (best_node == -1 || i < best_node) {
                    best_node = i;
                }
            }
        }
        
        if (best_node == -1) {
            // Cycle detected
            printf("ERROR\n");
            return 0;
        }
        
        result[result_count++] = best_node;
        
        // Decrease indegree of neighbors
        for (int v = 0; v < N; v++) {
            if (adj[best_node][v] > 0) {
                indeg[v] -= adj[best_node][v];
            }
        }
    }
    
    // Output the result
    for (int i = 0; i < result_count; i++) {
        printf("%d", result[i]);
        if (i < result_count - 1) {
            printf(" ");
        }
    }
    printf("\n");
    
    return 0;
}