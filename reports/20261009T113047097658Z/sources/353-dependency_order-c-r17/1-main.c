#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    // Adjacency list using linked lists to handle duplicates and self-loops naturally
    // We use an array of head indices for adjacency list
    // Since nodes are 0..N-1, we can use simple arrays
    
    // In-degree count
    int *indegree = calloc(N, sizeof(int));
    if (!indegree) return 1;

    // Adjacency list: for each node, store next edge index
    // We'll use a simple approach: collect all edges and build adjacency
    // Since N <= 20, we can use a fixed-size array for adjacency with linked lists
    
    int *head = calloc(N, sizeof(int));
    int *next = malloc(M * sizeof(int));
    if (!head || !next) {
        free(head);
        free(next);
        free(indegree);
        return 1;
    }

    // Initialize head to -1
    memset(head, -1, N * sizeof(int));

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        
        // Add edge u -> v
        next[i] = head[u];
        head[u] = i;
        indegree[v]++;
    }

    free(next);

    // Kahn's algorithm with priority queue simulation using a sorted list
    // Since N is small (<=20), we can use a simple approach:
    // Find all nodes with indegree 0, sort them, then process in order
    
    int *result = malloc(N * sizeof(int));
    if (!result) {
        free(head);
        free(indegree);
        return 1;
    }

    int count = 0;
    
    // To get lexicographically smallest ordering, we need to always pick the smallest available node
    // We'll use a simple approach: repeatedly find the smallest node with indegree 0
    
    for (int i = 0; i < N; i++) {
        int best_node = -1;
        
        // Find the smallest node with indegree 0
        for (int j = 0; j < N; j++) {
            if (indegree[j] == 0) {
                if (best_node == -1 || j < best_node) {
                    best_node = j;
                }
            }
        }
        
        if (best_node == -1) {
            // Cycle detected
            break;
        }
        
        result[count++] = best_node;
        indegree[best_node] = -1; // Mark as processed
        
        // Update in-degrees of neighbors
        for (int e = head[best_node]; e != -1; e = next[e]) {
            int v = 0;
            // We need to find the node that has edge from best_node to it
            // But our adjacency list stores edges, not reverse
            // Let's rebuild: we need to know which nodes are reachable from best_node
            // Actually, we stored edges in head[u] pointing to edge index
            // Each edge index points to next[edge_index] and we need to know the target
            // But we didn't store targets separately! We need to fix this.
        }
    }
    
    // Let's redo with proper adjacency list that stores targets
    free(head);
    free(indegree);
    
    // Reset and do it properly
    indegree = calloc(N, sizeof(int));
    head = calloc(N, sizeof(int));
    next = malloc(M * sizeof(int));
    if (!indegree || !head || !next) {
        free(head);
        free(indegree);
        free(next);
        return 1;
    }
    memset(head, -1, N * sizeof(int));

    // Also store target for each edge
    int *targets = malloc(M * sizeof(int));
    if (!targets) {
        free(head);
        free(indegree);
        free(next);
        return 1;
    }

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        
        next[i] = head[u];
        head[u] = i;
        targets[i] = v;
        indegree[v]++;
    }

    free(targets);

    // Now run Kahn's algorithm
    count = 0;
    
    for (int step = 0; step < N; step++) {
        int best_node = -1;
        
        // Find the smallest node with indegree 0
        for (int j = 0; j < N; j++) {
            if (indegree[j] == 0) {
                if (best_node == -1 || j < best_node) {
                    best_node = j;
                }
            }
        }
        
        if (best_node == -1) {
            break; // Cycle
        }
        
        result[count++] = best_node;
        indegree[best_node] = -1; // Mark as processed
        
        // Update neighbors
        for (int e = head[best_node]; e != -1; e = next[e]) {
            int v = targets[e];
            if (indegree[v] > 0) {
                indegree[v]--;
            }
        }
    }

    if (count < N) {
        printf("ERROR\n");
    } else {
        for (int i = 0; i < N; i++) {
            if (i > 0) printf(" ");
            printf("%d", result[i]);
        }
        printf("\n");
    }

    free(result);
    free(head);
    free(indegree);
    free(next);
    
    return 0;
}