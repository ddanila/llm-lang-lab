#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    // Adjacency list: head[u] -> list of v
    int *head = malloc(N > 0 ? N * sizeof(int) : 1);
    if (!head) return 1;
    for (int i = 0; i < N; i++) head[i] = -1;

    // In-degree array
    int *indegree = calloc(N, sizeof(int));
    if (!indegree) { free(head); return 1; }

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        // Add edge u -> v
        int e = head[u];
        if (e == -1) {
            head[u] = v;
        } else {
            while (head[u] != -1 && head[u] != v) {
                head[u] = head[head[u]];
            }
            // Actually we need to insert at front for simplicity, but we'll just add multiple edges
            // To handle duplicates correctly with topological sort, we should track unique neighbors
            // But simpler: use an adjacency list with linked nodes
        }
    }

    // Let's rebuild with proper linked list nodes
    free(head);
    head = NULL;
    indegree = NULL;

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

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        edge_to[i] = v;
        edge_next[i] = head_list[u];
        head_list[u] = i;
        indegree[v]++;
    }

    // Use a min-heap (priority queue) for Kahn's algorithm to get lexicographically smallest order
    // Since N <= 20, we can just use a simple array and scan for min each time
    int *degree = malloc(N * sizeof(int));
    if (!degree) { free(edge_to); free(edge_next); free(head_list); return 1; }
    for (int i = 0; i < N; i++) degree[i] = indegree[i];

    int result[20];
    int count = 0;

    // Find node with min degree (and among ties, smallest index)
    while (count < N) {
        int best = -1;
        int best_deg = N + 1;
        for (int i = 0; i < N; i++) {
            if (degree[i] == 0 && i < best || degree[i] < best_deg) {
                best = i;
                best_deg = degree[i];
            }
        }

        if (best == -1) {
            // Cycle detected
            printf("ERROR\n");
            free(edge_to); free(edge_next); free(head_list); free(degree);
            return 0;
        }

        result[count++] = best;
        degree[best] = -1; // mark as used

        // Decrease degree of neighbors
        for (int e = head_list[best]; e != -1; e = edge_next[e]) {
            int v = edge_to[e];
            degree[v]--;
        }
    }

    for (int i = 0; i < N; i++) {
        printf("%d%c", result[i], (i == N - 1) ? '\n' : ' ');
    }

    free(edge_to);
    free(edge_next);
    free(head_list);
    free(degree);
    return 0;
}