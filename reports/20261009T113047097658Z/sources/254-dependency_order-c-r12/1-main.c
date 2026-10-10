#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    // Adjacency list using linked lists for edges
    // adj[u] points to first edge from u
    // Edge struct: v is destination
    int *adj = calloc(N, sizeof(int));
    if (!adj) return 1;

    int indegree[20];
    for (int i = 0; i < N; i++) indegree[i] = 0;

    for (int i = 0; i < M; i++) {
        int u, v;
        if (scanf("%d %d", &u, &v) != 2) break;
        
        // Add edge u -> v
        adj[u] += adj[u]; // dummy to keep pointer valid, will fix below
        
        // Use a simple approach: store edges in an array and rebuild adjacency
    }

    // Re-implement with arrays for simplicity
    // Since N <= 20, we can use adjacency matrix or simple edge list
    
    // Free previous allocation (not needed as adj was just dummy)
    free(adj);

    // Use adjacency matrix since N is small
    int has_edge[20][20];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            has_edge[i][j] = 0;
        }
    }

    // Reset indegree
    for (int i = 0; i < N; i++) indegree[i] = 0;

    for (int i = 0; i < M; i++) {
        int u, v;
        if (scanf("%d %d", &u, &v) != 2) break;
        
        // Handle self-loops and duplicates - they don't affect topological sort logic
        // But we need to count indegrees correctly. A self-loop creates a cycle.
        if (u == v) {
            // Self-loop means cycle
            printf("ERROR\n");
            return 0;
        }
        
        has_edge[u][v] = 1;
        indegree[v]++;
    }

    // Kahn's algorithm with lexicographically smallest ordering
    // Use a min-heap or simply iterate to find minimum indegree 0 node each time
    
    int *order = malloc(N * sizeof(int));
    if (!order) return 1;
    
    int count = 0;
    
    for (int step = 0; step < N; step++) {
        // Find node with indegree 0, choosing smallest index first for lexicographic order
        int best = -1;
        for (int i = 0; i < N; i++) {
            if (indegree[i] == 0) {
                if (best == -1 || i < best) {
                    best = i;
                }
            }
        }
        
        if (best == -1) {
            // No node with indegree 0, cycle exists
            printf("ERROR\n");
            free(order);
            return 0;
        }
        
        order[count++] = best;
        indegree[best] = -1; // Mark as processed
        
        // Decrease indegree of neighbors
        for (int i = 0; i < N; i++) {
            if (has_edge[best][i]) {
                indegree[i]--;
            }
        }
    }
    
    // Output result
    for (int i = 0; i < N; i++) {
        printf("%d", order[i]);
        if (i < N - 1) printf(" ");
    }
    printf("\n");

    free(order);
    return 0;
}