#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    // Adjacency list using linked lists for edges
    // Each node has a head pointer to its first edge
    int *head = calloc(N > 0 ? N : 1, sizeof(int));
    if (!head) { free(head); return 0; }
    
    // In-degree array
    int *in_degree = calloc(N > 0 ? N : 1, sizeof(int));
    if (!in_degree) { free(head); free(in_degree); return 0; }

    // Store edges in a flat array for iteration, since linked lists make cycle detection harder
    // Actually, let's use adjacency list with edge count per node
    int *edge_count = calloc(N > 0 ? N : 1, sizeof(int));
    if (!edge_count) { free(head); free(in_degree); free(edge_count); return 0; }

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        // Self-loops create cycles, but we need to handle them
        // Duplicate edges are allowed but don't affect topological sort
        if (head[u] == -1) head[u] = i;
        edge_count[u]++;
    }

    // Reset head to -1 for proper adjacency list
    memset(head, -1, N * sizeof(int));
    
    // Re-read input or store edges differently
    // Let's re-implement with a simpler approach
    
    free(head);
    free(in_degree);
    free(edge_count);
    
    return 0;
}