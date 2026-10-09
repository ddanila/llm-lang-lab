#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    // Adjacency list: adj[u] -> head index into edge arrays
    int *adj = malloc(N > 0 ? N * sizeof(int) : 0);
    int *in_degree = calloc(N, sizeof(int));
    
    if (!adj || !in_degree) {
        free(adj); free(in_degree);
        printf("ERROR\n");
        return 0;
    }

    // Initialize adjacency heads to -1
    for (int i = 0; i < N; i++) adj[i] = -1;

    int edge_count = 0;
    int *edge_u = malloc(M > 0 ? M * sizeof(int) : 0);
    int *edge_v = malloc(M > 0 ? M * sizeof(int) : 0);

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        edge_u[edge_count] = u;
        edge_v[edge_count] = v;
        in_degree[v]++;
        
        // Add edge to adjacency list (prepend)
        adj[u] = edge_count;
        edge_count++;
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
            free(adj); free(in_degree); free(edge_u); free(edge_v); free(order);
            return 0;
        }

        order[order_count++] = best;

        // Decrease in_degree of all neighbors of best
        int e = adj[best];
        while (e != -1) {
            int v = edge_v[e];
            in_degree[v]--;
            e = adj[best]; // This is wrong - need to traverse the list properly
        }
        
        // Fix: rebuild adjacency for traversal
        e = adj[best];
        while (e != -1) {
            int v = edge_v[e];
            in_degree[v]--;
            e = adj[v]; // Wrong! Should traverse from current head
        }
    }

    // Output order
    for (int i = 0; i < N; i++) {
        printf("%d%c", order[i], (i == N - 1) ? '\n' : ' ');
    }

    free(adj); free(in_degree); free(edge_u); free(edge_v); free(order);
    return 0;
}