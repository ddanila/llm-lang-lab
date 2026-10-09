#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    // Adjacency list: adj_head[u] contains index of first edge from u
    // adj_next[e] is next edge index from same source
    // adj_to[e] is the destination node v for edge e
    
    int *adj_head = calloc(N, sizeof(int));
    int *adj_next = malloc(M > 0 ? M * sizeof(int) : 1);
    int *adj_to = malloc(M > 0 ? M * sizeof(int) : 1);
    
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj_next[i] = adj_head[u];
        adj_head[u] = i;
        adj_to[i] = v;
    }

    // Compute in-degrees
    int *indeg = calloc(N, sizeof(int));
    for (int u = 0; u < N; u++) {
        for (int e = adj_head[u]; e != -1; e = adj_next[e]) {
            indeg[adj_to[e]]++;
        }
    }

    // Kahn's algorithm: always pick smallest node with in-degree 0
    int *order = malloc(N * sizeof(int));
    int order_idx = 0;
    
    while (order_idx < N) {
        int best_node = -1;
        for (int i = 0; i < N; i++) {
            if (indeg[i] == 0 && (best_node == -1 || i < best_node)) {
                best_node = i;
            }
        }
        
        if (best_node == -1) {
            // Cycle detected
            printf("ERROR\n");
            free(adj_head);
            free(adj_next);
            free(adj_to);
            free(indeg);
            free(order);
            return 0;
        }
        
        order[order_idx++] = best_node;
        indeg[best_node]--; // Mark as removed
        
        for (int e = adj_head[best_node]; e != -1; e = adj_next[e]) {
            indeg[adj_to[e]]--;
        }
    }

    // Output result
    for (int i = 0; i < N; i++) {
        printf("%d%c", order[i], i == N - 1 ? '\n' : ' ');
    }

    free(adj_head);
    free(adj_next);
    free(adj_to);
    free(indeg);
    free(order);
    
    return 0;
}