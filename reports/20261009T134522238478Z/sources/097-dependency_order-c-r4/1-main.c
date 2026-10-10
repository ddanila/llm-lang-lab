#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    // Adjacency list using linked lists for each node
    struct Node {
        int to;
        struct Node *next;
    };
    struct Node **adj = malloc(N * sizeof(struct Node *));
    for (int i = 0; i < N; i++) adj[i] = NULL;

    // In-degree array
    int *indegree = calloc(N, sizeof(int));

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (u < 0 || u >= N || v < 0 || v >= N) continue;
        // Add edge u -> v
        struct Node *edge = malloc(sizeof(struct Node));
        edge->to = v;
        edge->next = adj[u];
        adj[u] = edge;
        indegree[v]++;
    }

    // Use a min-heap (priority queue) for lexicographically smallest topological order
    // Since N <= 20, we can use a simple array and scan for minimum
    int *order = malloc(N * sizeof(int));
    int count = 0;

    // Initially, all nodes with indegree 0 are available
    int *available = calloc(N, sizeof(int));
    int avail_count = 0;
    for (int i = 0; i < N; i++) {
        if (indegree[i] == 0) {
            available[avail_count++] = i;
        }
    }

    while (avail_count > 0) {
        // Find the smallest index in available
        int min_node = -1;
        for (int i = 0; i < avail_count; i++) {
            if (min_node == -1 || available[i] < min_node) {
                min_node = available[i];
            }
        }

        // Remove min_node from available
        int idx = -1;
        for (int i = 0; i < avail_count; i++) {
            if (available[i] == min_node) {
                idx = i;
                break;
            }
        }
        // Shift elements after idx to fill the gap
        for (int i = idx; i < avail_count - 1; i++) {
            available[i] = available[i + 1];
        }
        avail_count--;

        order[count++] = min_node;

        // Process neighbors of min_node
        struct Node *edge = adj[min_node];
        while (edge != NULL) {
            int v = edge->to;
            indegree[v]--;
            if (indegree[v] == 0) {
                available[avail_count++] = v;
            }
            edge = edge->next;
        }
    }

    // Check if all nodes are ordered (no cycle)
    if (count != N) {
        printf("ERROR\n");
    } else {
        for (int i = 0; i < N; i++) {
            if (i > 0) printf(" ");
            printf("%d", order[i]);
        }
        printf("\n");
    }

    free(adj);
    free(indegree);
    free(order);
    free(available);

    return 0;
}