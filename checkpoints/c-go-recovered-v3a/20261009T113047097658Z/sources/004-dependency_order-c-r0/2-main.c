#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    if (N == 0) {
        printf("\n");
        return 0;
    }

    // Adjacency list using arrays for edges
    int *head = malloc(N * sizeof(int));
    int *next = calloc(M, sizeof(int));
    int *to = calloc(M, sizeof(int));
    int edge_count = 0;

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        to[edge_count] = v;
        next[edge_count] = head[u];
        head[u] = edge_count++;
    }

    // In-degree array
    int *indegree = calloc(N, sizeof(int));
    for (int i = 0; i < N; i++) {
        for (int e = head[i]; e != -1; e = next[e]) {
            indegree[to[e]]++;
        }
    }

    // Simple array to track nodes with indegree 0, keep sorted
    int *zero_indegree = malloc(N * sizeof(int));
    int zero_count = 0;
    
    for (int i = 0; i < N; i++) {
        if (indegree[i] == 0) {
            zero_indegree[zero_count++] = i;
        }
    }

    // Keep the array sorted by repeatedly finding min and removing it
    int result_count = 0;
    int *result = malloc(N * sizeof(int));

    while (zero_count > 0) {
        // Find minimum element
        int u = zero_indegree[0];
        for (int i = 1; i < zero_count; i++) {
            if (zero_indegree[i] < u) {
                u = zero_indegree[i];
            }
        }

        result[result_count++] = u;

        // Remove u from array by shifting
        int removed = -1;
        for (int i = 0; i < zero_count; i++) {
            if (zero_indegree[i] == u) {
                removed = i;
                break;
            }
        }
        for (int i = removed; i < zero_count - 1; i++) {
            zero_indegree[i] = zero_indegree[i + 1];
        }
        zero_count--;

        // Process neighbors
        for (int e = head[u]; e != -1; e = next[e]) {
            int v = to[e];
            if (--indegree[v] == 0) {
                // Insert v into sorted position
                int idx = 0;
                while (idx < zero_count && zero_indegree[idx] < v) {
                    idx++;
                }
                for (int i = zero_count; i > idx; i--) {
                    zero_indegree[i] = zero_indegree[i - 1];
                }
                zero_indegree[idx] = v;
                zero_count++;
            }
        }
    }

    if (result_count != N) {
        printf("ERROR\n");
    } else {
        for (int i = 0; i < N; i++) {
            printf("%d%c", result[i], (i == N - 1 ? '\n' : ' '));
        }
    }

    free(head);
    free(next);
    free(to);
    free(indegree);
    free(zero_indegree);
    free(result);

    return 0;
}