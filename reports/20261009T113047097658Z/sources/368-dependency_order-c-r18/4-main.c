#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    // Adjacency list using parallel arrays for linked lists
    // head[u] = index into edge_list where the first edge from u is stored
    // edge_list[i].to stores the target of edge i
    // next[i] stores the next edge index from the same source
    
    int *edge_to = malloc(M * sizeof(int));
    int *next = malloc(M * sizeof(int));
    int *head = calloc(N, sizeof(int));
    
    for (int i = 0; i < N; i++) head[i] = -1;

    // Read M edges
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        edge_to[i] = v;
        next[i] = head[u];
        head[u] = i;
    }

    // Compute in-degrees
    int *indegree = calloc(N, sizeof(int));
    for (int u = 0; u < N; u++) {
        for (int e = head[u]; e != -1; e = next[e]) {
            indegree[edge_to[e]]++;
        }
    }

    // Kahn's algorithm to get lexicographically smallest ordering
    int *order = malloc(N * sizeof(int));
    int order_count = 0;

    for (int i = 0; i < N; i++) {
        // Find smallest index j such that indegree[j] == 0 and not yet ordered
        int best = -1;
        for (int j = 0; j < N && order_count < N; j++) {
            if (indegree[j] == 0) {
                if (best == -1 || j < best) {
                    best = j;
                }
            }
        }
        
        if (best == -1) {
            printf("ERROR\n");
            free(edge_to);
            free(next);
            free(head);
            free(indegree);
            free(order);
            return 0;
        }

        order[order_count++] = best;
        indegree[best] = -1; // Mark as used
        
        // Decrease in-degree of neighbors
        for (int e = head[best]; e != -1; e = next[e]) {
            int v = edge_to[e];
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

    free(edge_to);
    free(next);
    free(head);
    free(indegree);
    free(order);
    return 0;
}