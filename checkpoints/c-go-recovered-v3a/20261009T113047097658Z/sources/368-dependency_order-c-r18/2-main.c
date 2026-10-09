#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    // Adjacency list: adj[u] = list of v using parallel arrays
    // head[u] = index into edges array where edge from u starts
    // We'll store edges as pairs in a simple struct
    typedef struct { int to, next; } Edge;
    Edge *edges = malloc(N * sizeof(Edge));
    if (!edges) return 0;
    
    // Initialize head with -1
    for (int i = 0; i < N; i++) edges[i].next = -1;

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        // Edge u -> v: u must come before v
        edges[u].to = v;
        edges[u].next = -1;  // overwrite each time (simple adjacency list where we just store last edge)
    }

    // Actually need proper linked list. Let me redo.
    // Simpler approach: use an array of vectors simulated with linked lists
    Edge *edge_list = malloc(M * sizeof(Edge));
    int *head = calloc(N, sizeof(int));
    
    for (int i = 0; i < N; i++) head[i] = -1;

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        edge_list[i].to = v;
        edge_list[i].next = head[u];
        head[u] = i;
    }

    // Compute in-degrees
    int *indegree = calloc(N, sizeof(int));
    for (int u = 0; u < N; u++) {
        for (int e = head[u]; e != -1; e = edge_list[e].next) {
            indegree[edge_list[e].to]++;
        }
    }

    // Kahn's algorithm with a min-heap priority queue to get lexicographically smallest ordering
    // Since N is small (<=20), we can use a simple approach: repeatedly find the smallest node with in-degree 0
    
    int *order = malloc(N * sizeof(int));
    int order_count = 0;

    for (int i = 0; i < N; i++) {
        // Find smallest index j such that indegree[j] == 0 and j is not yet ordered
        int best = -1;
        for (int j = 0; j < N && order_count < N; j++) {
            if (indegree[j] == 0) {
                if (best == -1 || j < best) {
                    best = j;
                }
            }
        }
        
        if (best == -1) {
            // No node with in-degree 0, cycle exists
            printf("ERROR\n");
            free(edges);
            free(head);
            free(indegree);
            free(order);
            return 0;
        }

        order[order_count++] = best;
        indegree[best] = -1; // Mark as used
        
        // Decrease in-degree of neighbors
        for (int e = head[best]; e != -1; e = edge_list[e].next) {
            int v = edge_list[e].to;
            if (indegree[v] > 0) {
                indegree[v]--;
            }
        }
    }

    // Output the ordering
    for (int i = 0; i < N; i++) {
        printf("%d", order[i]);
        if (i < N - 1) printf(" ");
    }
    printf("\n");

    free(edges);
    free(head);
    free(indegree);
    free(order);
    return 0;
}