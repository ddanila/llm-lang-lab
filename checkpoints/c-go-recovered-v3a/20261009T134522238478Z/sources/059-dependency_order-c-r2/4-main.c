#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    // For small N <= 20, we can use a simple adjacency matrix or list.
    
    int *indeg = calloc(N, sizeof(int));
    int *head = malloc(N * sizeof(int));
    int *next = malloc(M * sizeof(int));
    int *to = malloc(M * sizeof(int));

    for (int i = 0; i < N; i++) head[i] = -1;

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        
        // Check for self-loop
        if (u == v) {
            printf("ERROR\n");
            free(indeg); free(head); free(next); free(to);
            return 0;
        }
        
        // Add edge u -> v
        next[i] = head[u];
        to[i] = v;
        head[u] = i;
        indeg[v]++;
    }

    int *result = malloc(N * sizeof(int));
    int count = 0;

    while (count < N) {
        int min_node = -1;
        
        // Find the smallest node index with indegree 0
        for (int i = 0; i < N; i++) {
            if (indeg[i] == 0) {
                if (min_node == -1 || i < min_node) {
                    min_node = i;
                }
            }
        }

        if (min_node == -1) {
            // No node with indegree 0 -> cycle exists
            printf("ERROR\n");
            free(indeg); free(head); free(next); free(to); free(result);
            return 0;
        }

        result[count++] = min_node;

        // Decrease indegree of neighbors
        for (int e = head[min_node]; e != -1; e = next[e]) {
            int v = to[e];
            indeg[v]--;
        }
    }

    for (int i = 0; i < N; i++) {
        printf("%d%c", result[i], (i == N - 1) ? '\n' : ' ');
    }

    free(indeg); free(head); free(next); free(to); free(result);
    return 0;
}