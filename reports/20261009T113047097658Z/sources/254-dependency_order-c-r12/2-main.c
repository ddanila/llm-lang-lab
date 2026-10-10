#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    // Handle N=0 case
    if (N == 0) {
        printf("\n");
        return 0;
    }

    // Adjacency matrix since N <= 20
    int has_edge[20][20];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            has_edge[i][j] = 0;
        }
    }

    // Reset indegree
    int indegree[20];
    for (int i = 0; i < N; i++) indegree[i] = 0;

    for (int i = 0; i < M; i++) {
        int u, v;
        if (scanf("%d %d", &u, &v) != 2) break;
        
        // Self-loop means cycle
        if (u == v) {
            has_edge[u][v] = 1;
            indegree[v]++;
        } else {
            has_edge[u][v] = 1;
            indegree[v]++;
        }
    }

    // Kahn's algorithm with lexicographically smallest ordering
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