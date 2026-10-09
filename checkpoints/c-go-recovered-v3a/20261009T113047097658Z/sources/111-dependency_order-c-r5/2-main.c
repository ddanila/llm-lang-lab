#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    // Adjacency list using arrays for efficiency
    struct EdgeNode {
        int v;
        struct EdgeNode *next;
    };
    struct EdgeNode **adj = malloc(N * sizeof(struct EdgeNode*));
    for (int i = 0; i < N; i++) adj[i] = NULL;

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        struct EdgeNode *e = malloc(sizeof(struct EdgeNode));
        e->v = v;
        e->next = adj[u];
        adj[u] = e;
    }

    // Compute in-degrees
    int *indeg = calloc(N, sizeof(int));
    for (int u = 0; u < N; u++) {
        struct EdgeNode *e = adj[u];
        while (e) {
            indeg[e->v]++;
            e = e->next;
        }
    }

    // Use a min-heap or simply iterate to find smallest available node
    int *order = malloc(N * sizeof(int));
    int order_count = 0;

    int *indeg_copy = malloc(N * sizeof(int));
    memcpy(indeg_copy, indeg, N * sizeof(int));

    // Repeatedly find node with indegree 0 among remaining nodes
    for (int step = 0; step < N; step++) {
        int best_node = -1;
        for (int i = 0; i < N; i++) {
            if (indeg_copy[i] == 0) {
                if (best_node == -1 || i < best_node) {
                    best_node = i;
                }
            }
        }

        if (best_node == -1) {
            // Cycle detected
            free(adj);
            free(indeg);
            free(order);
            free(indeg_copy);
            printf("ERROR\n");
            return 0;
        }

        order[order_count++] = best_node;
        indeg_copy[best_node] = -1; // Mark as used

        struct EdgeNode *e = adj[best_node];
        while (e) {
            int v = e->v;
            indeg_copy[v]--;
            e = e->next;
        }
    }

    for (int i = 0; i < N; i++) {
        if (i > 0) printf(" ");
        printf("%d", order[i]);
    }
    printf("\n");

    free(adj);
    free(indeg);
    free(order);
    free(indeg_copy);
    return 0;
}