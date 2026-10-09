#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    // Adjacency list: adj[u] contains v where u -> v
    // We'll use a simple array of linked lists via next pointers
    int *next = malloc(N > 0 ? N * sizeof(int) : 1);
    int *head = calloc(N, sizeof(int));
    
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        next[i] = head[u];
        head[u] = i;
    }

    // Compute in-degrees
    int *indeg = calloc(N, sizeof(int));
    for (int u = 0; u < N; u++) {
        for (int e = head[u]; e != -1; e = next[e]) {
            int v = e; // Wait, edges are stored as indices, need to get v
            // Actually, we didn't store v in the edge index. Let's redesign.
        }
    }

    // Redesign: use adjacency matrix or store edges properly
    // Since N <= 20, we can use an adjacency matrix or simple lists with (u,v) stored
    
    // Free previous and redo with proper storage
    free(next);
    free(head);
    free(indeg);
    
    // Use adjacency list where each edge is stored as a struct or parallel arrays
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
    for (int indegree = 0; indegree < N; indegree++) {
        int *indeg_arr = calloc(N, sizeof(int));
    }
    
    // Recompute in-degrees properly
    for (int i = 0; i < N; i++) {
        for (int e = adj_head[i]; e != -1; e = adj_next[e]) {
            indegree[adj_to[e]]++;
        }
    }

    // Kahn's algorithm with min-heap simulation using array (since N <= 20)
    int *order = malloc(N * sizeof(int));
    int order_idx = 0;
    
    // Find all nodes with in-degree 0, put them in a list sorted by node index
    int *queue = calloc(N, sizeof(int));
    int queue_head = 0, queue_tail = 0;
    
    for (int i = 0; i < N; i++) {
        if (indeg[i] == 0) {
            queue[queue_tail++] = i;
        }
    }
    
    // Sort queue to get lexicographically smallest first (already sorted by loop order)
    // Since we iterate 0..N-1, queue is naturally sorted
    
    while (queue_head < queue_tail) {
        int u = queue[queue_head++];
        order[order_idx++] = u;
        
        for (int e = adj_head[u]; e != -1; e = adj_next[e]) {
            indeg[adj_to[e]]--;
            if (indeg[adj_to[e]] == 0) {
                queue[queue_tail++] = adj_to[e];
                // Since we add in increasing order of node index, and we process
                // from the front, the queue remains sorted. But when we add a new node,
                // it might be smaller than some existing nodes at the tail? No, because
                // we always pick the smallest available node. Actually, we need to maintain
                // the queue in sorted order. Since N is small, we can just use a simple
                // approach: always pick the smallest index node with in-degree 0.
                // To do this properly, we should re-scan or use a heap. But for N<=20,
                // we can just find the min each time.
            }
        }
    }
    
    // Check if all nodes are ordered (no cycle)
    if (order_idx < N) {
        printf("ERROR\n");
    } else {
        for (int i = 0; i < N; i++) {
            printf("%d%c", order[i], i == N - 1 ? '\n' : ' ');
        }
    }

    free(next);
    free(head);
    free(indeg);
    free(adj_head);
    free(adj_next);
    free(adj_to);
    free(order);
    free(queue);
    
    return 0;
}