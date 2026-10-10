#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    // Adjacency list: adj[u] contains list of v such that u -> v
    int *adj = NULL;
    int *count = NULL;
    int *indegree = NULL;
    int cap = N + 1;
    int idx = 0;

    if (N > 0) {
        adj = malloc(cap * sizeof(int));
        count = malloc(cap * sizeof(int));
        indegree = malloc(cap * sizeof(int));
        memset(count, 0, cap * sizeof(int));
        memset(indegree, 0, cap * sizeof(int));
    }

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (N > 0) {
            adj[idx] = v;
            count[idx++] = 1; // simple list, we'll manage separately
            indegree[v]++;
        }
    }

    // Use a simpler adjacency representation: for each u, store next edge index
    int *head = NULL;
    int *next_edge = NULL;
    int *edge_to = NULL;
    if (N > 0) {
        head = calloc(N, sizeof(int));
        next_edge = malloc(M * sizeof(int));
        edge_to = malloc(M * sizeof(int));
        memset(head, -1, N * sizeof(int));
        for (int i = 0; i < M; i++) {
            int u, v;
            scanf("%d %d", &u, &v); // Need to re-read? No, we already read all edges.
            // Oops, we need to store edges properly. Let's redesign.
        }
    }

    return 0;
}