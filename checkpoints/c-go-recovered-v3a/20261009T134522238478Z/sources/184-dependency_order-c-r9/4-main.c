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

    // Allocate adjacency list using arrays for edges
    int *edge_to = malloc(M > 0 ? M * sizeof(int) : 1);
    int *edge_next = malloc(M > 0 ? M * sizeof(int) : 1);
    int *head_list = calloc(N, sizeof(int));

    if (!edge_to || !edge_next || !head_list) {
        free(edge_to); free(edge_next); free(head_list);
        return 1;
    }

    // Read M edges
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        edge_to[i] = v;
        edge_next[i] = head_list[u];
        head_list[u] = i;
    }

    // Compute in-degrees
    int *indegree = malloc(N * sizeof(int));
    if (!indegree) { free(edge_to); free(edge_next); free(head_list); return 1; }
    
    for (int u = 0; u < N; u++) {
        for (int e = head_list[u]; e != -1; e = edge_next[e]) {
            indegree[edge_to[e]]++;
        }
    }

    // Use Kahn's algorithm with min-heap approach (scan for smallest index with degree 0)
    int *degree = malloc(N * sizeof(int));
    if (!degree) { free(edge_to); free(edge_next); free(head_list); free(indegree); return 1; }
    for (int i = 0; i < N; i++) degree[i] = indegree[i];

    int result[20];
    int count = 0;

    // Find node with min degree (and among ties, smallest index)
    while (count < N) {
        int best = -1;
        for (int i = 0; i < N; i++) {
            if (degree[i] == 0) {
                best = i;
                break; // found smallest index with degree 0
            }
        }

        if (best == -1) {
            // Cycle detected
            printf("ERROR\n");
            free(edge_to); free(edge_next); free(head_list); free(indegree); free(degree);
            return 0;
        }

        result[count++] = best;
        degree[best] = -1; // mark as used

        // Decrease degree of neighbors
        for (int e = head_list[best]; e != -1; e = edge_next[e]) {
            int v = edge_to[e];
            if (degree[v] > 0) {
                degree[v]--;
            }
        }
    }

    for (int i = 0; i < N; i++) {
        printf("%d%c", result[i], (i == N - 1) ? '\n' : ' ');
    }

    free(edge_to);
    free(edge_next);
    free(head_list);
    free(indegree);
    free(degree);
    return 0;
}