#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    // Adjacency list: adj[u] = list of v
    // We'll use a simple array-based approach with linked lists via next pointers
    int *head = calloc(N, sizeof(int));
    int *next = malloc(M * sizeof(int));
    if (!head || !next) {
        free(head); free(next);
        return 0;
    }
    memset(head, -1, N * sizeof(int));

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        // Edge u -> v: u must come before v
        next[i] = head[u];
        head[u] = i;
    }

    // In-degree array
    int *indegree = calloc(N, sizeof(int));
    for (int u = 0; u < N; u++) {
        for (int e = head[u]; e != -1; e = next[e]) {
            int v = /* need to store target */; // We didn't store targets, need fix
        }
    }

    free(head); free(next); free(indegree);
    return 0;
}