#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    if (N == 0 && M == 0) {
        printf("\n");
        return 0;
    }

    // Adjacency list: head[u] -> first edge from u
    int *head = calloc(N, sizeof(int));
    int *next = malloc(M * sizeof(int));
    int indegree[100];
    memset(head, -1, N * sizeof(int));
    memset(indegree, 0, N * sizeof(int));

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        // Add edge u -> v
        next[i] = head[u];
        head[u] = i;
        indegree[v]++;
    }

    // Kahn's algorithm with min-heap simulation using array + selection
    // We need lexicographically smallest ordering.
    // At each step, among all nodes with indegree 0, pick the smallest index.
    // Since N <= 20, we can just scan for min each time.

    int *order = malloc(N * sizeof(int));
    int order_count = 0;

    while (order_count < N) {
        int min_node = -1;
        int min_indegree = 2147483647; // effectively infinity

        for (int i = 0; i < N; i++) {
            if (indegree[i] == 0) {
                if (min_node == -1 || i < min_node) {
                    min_node = i;
                    min_indegree = 0;
                }
            }
        }

        if (min_node == -1) {
            // Cycle detected
            free(head);
            free(next);
            free(order);
            printf("ERROR\n");
            return 0;
        }

        order[order_count++] = min_node;
        indegree[min_node] = -1; // mark as processed

        // Decrease indegree of neighbors
        for (int e = head[min_node]; e != -1; e = next[e]) {
            int v = /* we need to know target */ ; // Problem: we didn't store targets in next
            // We need to restructure: store targets in an array
        }
    }

    free(head);
    free(next);
    free(order);
    return 0;
}