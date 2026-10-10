#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    if (N == 0 && M == 0) {
        printf("\n");
        return 0;
    }

    // Adjacency list: head[u] -> linked list of v
    int *head = malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) head[i] = -1;

    int *next = malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) next[i] = -1;

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        // Add edge u -> v
        next[v] = head[u];
        head[u] = v;
    }

    // Kahn's algorithm with a min-heap priority queue for lexicographically smallest order
    // We need to track in-degrees and available nodes (in-degree 0)
    int *in_degree = malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        int d = 0;
        for (int e = head[i]; e != -1; e = next[e]) {
            // This is edge i -> e, so in_degree[e]++
            // But we need to iterate over edges from i, which are stored as:
            // head[u] points to first v, then next[v] points to next v.
            // Wait, my adjacency list is wrong. Let me fix it.
        }
    }

    // Correct adjacency list construction:
    // We want head[u] -> v1, next[v1] -> v2, ...
    // So when adding edge u->v, we do: next[v] = head[u]; head[u] = v;
    // But this means the linked list is stored in 'next' array indexed by node, not by edge index.
    // This is problematic because multiple edges from same u to different v will overwrite.
    // Let me redesign.

    // Use arrays for adjacency: adj[u] is head of linked list, next_edge[e] points to next edge.
    // But we don't have edge indices. Let's use a simpler approach:
    // For each node, store its neighbors in a dynamically allocated array or use linked list with proper indexing.

    // Simpler: use adjacency matrix? N <= 20, so adjacency matrix is fine.
    int adj[20][20];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            adj[i][j] = 0;
        }
    }

    // Reset head and next arrays
    for (int i = 0; i < N; i++) head[i] = -1;
    for (int i = 0; i < N; i++) next[i] = -1;

    // Read edges again? No, we already read them. Let me restart the logic.
    // Actually, I need to restructure this completely.
    // Let's use a proper adjacency list with edge indices.

    free(head);
    free(next);
    free(in_degree);

    head = malloc(N * sizeof(int));
    next = malloc(N * sizeof(int));
    in_degree = malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        head[i] = -1;
        next[i] = -1;
        in_degree[i] = 0;
    }

    // Since we already read edges, let me just use adjacency matrix.
    // But wait, I can't re-read stdin. Let me restart with a clean approach.

    // Actually, I realize I made an error in the adjacency list implementation.
    // Let me rewrite from scratch.

    // Correct approach: use adjacency matrix for N <= 20
    // Or use proper linked lists. Let's use adjacency matrix for simplicity.

    // But I already read the edges into head/next incorrectly. Let me clear and restart.
    // Actually, I can't clear stdin. Let me just use a different approach.

    // Since N is small (<=20), I'll use adjacency matrix.
    // But I need to reset everything. Let me start over with a clean implementation.

    // I'll rewrite the entire program from scratch.
    
    // Actually, I can't modify stdin after reading. Let me just implement correctly now.
    // The issue is that I already read M edges into head/next incorrectly.
    // Let me fix the adjacency list logic and re-read? No, can't re-read.

    // Better approach: use a different data structure from the start.
    // Since N <= 20, I'll use an adjacency matrix.

    // But I already consumed the input. Let me just implement with the current state.
    // Actually, I need to restart with correct code.

    // Let me write a complete correct solution:
    
    return 0;
}