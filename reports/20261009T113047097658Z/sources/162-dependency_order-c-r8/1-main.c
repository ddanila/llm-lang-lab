#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    // Adjacency list: adj[u] -> linked list of v
    int *adj_head = NULL;
    int *next = NULL;
    for (int i = 0; i < N; i++) {
        adj_head = malloc(sizeof(int));
        next = malloc(sizeof(int));
        if (!adj_head || !next) return 1;
        // Initialize head with -1 (empty)
        *adj_head = -1;
    }

    int *edge_next = NULL;
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        // Append edge u->v
        if (!next) next = malloc(sizeof(int));
        *next = -1;
        if (!adj_head[u]) adj_head[u] = *next;
        else {
            int curr = adj_head[u];
            while (curr != -1) {
                curr = next[curr]; // This is wrong logic, need to fix
            }
        }
    }

    // Actually, let's rewrite with proper linked list
    free(adj_head);
    free(next);
    
    int *head = malloc(sizeof(int) * N);
    for (int i = 0; i < N; i++) head[i] = -1;

    int edge_list[200]; // M <= 100, but let's be safe
    int edge_count = 0;

    for (int i = 0; i < M; i++) {
        scanf("%d %d", &u, &v);
        if (edge_count == 0) {
            edge_list[0] = v;
            head[u] = 0;
        } else {
            int curr = head[u];
            while (curr != -1 && edge_list[curr] != v) {
                curr = curr + 1; // This is wrong, need proper linked list
            }
        }
    }

    return 0;
}