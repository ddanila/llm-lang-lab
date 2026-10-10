#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    // For N=0, M=0 output empty line
    if (N == 0 && M == 0) {
        printf("\n");
        return 0;
    }

    // Store edges: from[u] -> list of (to, edge_index)
    // We'll use a simple adjacency list where next[e] points to next edge index from same source
    // But we also need to know the target for each edge. Let's store targets in an array.
    
    int *head = calloc(N, sizeof(int));
    int *next = malloc(M * sizeof(int));
    int *target = malloc(M * sizeof(int));
    int indegree[100];
    memset(head, -1, N * sizeof(int));
    memset(indegree, 0, N * sizeof(int));

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        next[i] = head[u];
        head[u] = i;
        target[i] = v;
        indegree[v]++;
    }

    int *order = malloc(N * sizeof(int));
    int order_count = 0;

    while (order_count < N) {
        int min_node = -1;
        
        // Find node with indegree 0 and smallest index
        for (int i = 0; i < N; i++) {
            if (indegree[i] == 0) {
                if (min_node == -1 || i < min_node) {
                    min_node = i;
                }
            }
        }

        if (min_node == -1) {
            // Cycle detected
            free(head);
            free(next);
            free(target);
            free(order);
            printf("ERROR\n");
            return 0;
        }

        order[order_count++] = min_node;
        indegree[min_node] = -1; // mark as processed

        // Decrease indegree of neighbors
        for (int e = head[min_node]; e != -1; e = next[e]) {
            int v = target[e];
            if (indegree[v] > 0) {
                indegree[v]--;
            }
        }
    }

    // Output the ordering
    for (int i = 0; i < N; i++) {
        printf("%d", order[i]);
        if (i < N - 1) {
            printf(" ");
        }
    }
    printf("\n");

    free(head);
    free(next);
    free(target);
    free(order);
    return 0;
}