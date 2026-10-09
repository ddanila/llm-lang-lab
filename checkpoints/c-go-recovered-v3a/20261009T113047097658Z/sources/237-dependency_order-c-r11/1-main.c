#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    // Adjacency list: adj[u] -> linked list of v
    int *adj = malloc(N > 0 ? N * sizeof(int) : 0);
    int *in_degree = calloc(N, sizeof(int));
    int *count = calloc(N, sizeof(int)); // count edges per node for quick removal

    if (!adj || !in_degree || !count) {
        free(adj); free(in_degree); free(count);
        printf("ERROR\n");
        return 0;
    }

    // Initialize adjacency lists with head pointers (using index into adj array)
    // We'll use a simple linked list stored in an edge array for simplicity.
    int edge_count = 0;
    int *edge_u = malloc(M > 0 ? M * sizeof(int) : 0);
    int *edge_v = malloc(M > 0 ? M * sizeof(int) : 0);

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        edge_u[edge_count] = u;
        edge_v[edge_count] = v;
        in_degree[v]++;
        count[u]++;
        edge_count++;
    }

    // Use a min-heap (priority queue) to always pick the smallest available node.
    // Since N <= 20, we can just scan for the smallest in_degree == 0 node each time.
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
            // Cycle detected
            printf("ERROR\n");
            free(adj); free(in_degree); free(count); free(edge_u); free(edge_v); free(order);
            return 0;
        }

        order[order_count++] = best;

        // Decrease in_degree of all neighbors of best
        for (int i = 0; i < edge_count; i++) {
            if (edge_u[i] == best) {
                int v = edge_v[i];
                in_degree[v]--;
            }
        }
    }

    // Output order
    for (int i = 0; i < N; i++) {
        printf("%d%c", order[i], (i == N - 1) ? '\n' : ' ');
    }

    free(adj); free(in_degree); free(count); free(edge_u); free(edge_v); free(order);
    return 0;
}