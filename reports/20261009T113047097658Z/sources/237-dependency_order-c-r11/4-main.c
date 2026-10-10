#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    // For each node, store list of outgoing edges as linked list
    // adj[u] points to next edge index, but we need to traverse properly
    // Let's use a simpler approach: store all edges in arrays and traverse via iteration
    
    int *in_degree = calloc(N, sizeof(int));
    
    if (!in_degree) {
        printf("ERROR\n");
        return 0;
    }

    // Store all edges
    int *edge_u = malloc(M > 0 ? M * sizeof(int) : 0);
    int *edge_v = malloc(M > 0 ? M * sizeof(int) : 0);

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        edge_u[i] = u;
        edge_v[i] = v;
        in_degree[v]++;
    }

    int *order = malloc(N > 0 ? N * sizeof(int) : 0);
    int order_count = 0;

    while (order_count < N) {
        int best = -1;
        // Find smallest node with in_degree 0
        for (int i = 0; i < N; i++) {
            if (in_degree[i] == 0 && best == -1) {
                best = i;
            } else if (in_degree[i] == 0 && best != -1) {
                if (i < best) best = i;
            }
        }

        if (best == -1) {
            printf("ERROR\n");
            free(in_degree); free(edge_u); free(edge_v); free(order);
            return 0;
        }

        order[order_count++] = best;

        // Decrease in_degree of all neighbors of best by scanning all edges
        for (int i = 0; i < M; i++) {
            if (edge_u[i] == best) {
                in_degree[edge_v[i]]--;
            }
        }
    }

    // Output order
    for (int i = 0; i < N; i++) {
        printf("%d%c", order[i], (i == N - 1) ? '\n' : ' ');
    }

    free(in_degree); free(edge_u); free(edge_v); free(order);
    return 0;
}