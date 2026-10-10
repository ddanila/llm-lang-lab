#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    // Adjacency list for graph
    int *head = malloc(N > 0 ? sizeof(int) * N : 1);
    int *next = malloc(M >= 0 ? sizeof(int) * M : 1);
    int *to = malloc(M >= 0 ? sizeof(int) * M : 1);
    
    if (!head || !next || !to) { free(head); free(next); free(to); return 1; }

    // Initialize head to -1 (no edges)
    memset(head, -1, N > 0 ? N * sizeof(int) : 1);
    
    int edge_count = 0;
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        
        // Check bounds just in case
        if (u < 0 || u >= N || v < 0 || v >= N) continue;
        
        to[edge_count] = v;
        next[edge_count] = head[u];
        head[u] = edge_count++;
    }

    // Compute in-degrees
    int *in_degree = calloc(N, sizeof(int));
    if (!in_degree) { free(head); free(next); free(to); return 1; }

    for (int u = 0; u < N; u++) {
        for (int e = head[u]; e != -1; e = next[e]) {
            in_degree[to[e]]++;
        }
    }

    // Priority queue using a simple array with linear scan for min
    // We want lexicographically smallest, so we always pick the smallest available node
    int *order = malloc(N > 0 ? sizeof(int) * N : 1);
    if (!order) { free(head); free(next); free(to); free(in_degree); return 1; }

    int idx = 0;
    while (idx < N) {
        int min_node = -1;
        for (int i = 0; i < N; i++) {
            if (in_degree[i] == 0 && min_node == -1) {
                min_node = i;
            } else if (in_degree[i] == 0 && i < min_node) {
                min_node = i;
            }
        }

        if (min_node == -1) {
            // Cycle detected
            break;
        }

        order[idx++] = min_node;
        in_degree[min_node] = -1; // Mark as processed

        // Decrease in-degree of neighbors
        for (int e = head[min_node]; e != -1; e = next[e]) {
            int v = to[e];
            if (in_degree[v] > 0) {
                in_degree[v]--;
            }
        }
    }

    // Check if we processed all nodes
    if (idx < N) {
        printf("ERROR\n");
    } else {
        for (int i = 0; i < N; i++) {
            printf("%d", order[i]);
            if (i < N - 1) printf(" ");
        }
        printf("\n");
    }

    free(head);
    free(next);
    free(to);
    free(in_degree);
    free(order);
    
    return 0;
}