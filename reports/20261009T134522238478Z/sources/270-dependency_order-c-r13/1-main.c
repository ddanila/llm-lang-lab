#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    if (N == 0 && M == 0) {
        printf("\n");
        return 0;
    }

    // Adjacency list: adj[u] -> list of v
    int *adj = NULL;
    int *count_adj = NULL;
    int capacity = N + 1;
    int total_edges = 0;

    if (N > 0) {
        adj = malloc(capacity * sizeof(int));
        count_adj = calloc(capacity, sizeof(int));
    }

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (count_adj[u] < capacity) {
            adj[count_adj[u]] = v;
            count_adj[u]++;
        } else {
            // Resize if needed (unlikely given constraints but for safety)
            int new_cap = capacity * 2;
            int *new_adj = realloc(adj, new_cap * sizeof(int));
            int *new_count = realloc(count_adj, new_cap * sizeof(int));
            if (!new_adj || !new_count) {
                free(adj);
                free(count_adj);
                return 1;
            }
            adj = new_adj;
            count_adj = new_count;
            // Extend count for new nodes
            for (int j = capacity; j < new_cap; j++) count_adj[j] = 0;
            capacity = new_cap;
            adj[count_adj[u]] = v;
            count_adj[u]++;
        }
    }

    // Compute in-degrees
    int *in_degree = calloc(N, sizeof(int));
    for (int u = 0; u < N; u++) {
        for (int i = 0; i < count_adj[u]; i++) {
            int v = adj[u + i];
            in_degree[v]++;
        }
    }

    // Kahn's algorithm with min-heap simulation using a fixed array and sorting
    // Since N <= 20, we can just collect nodes with in-degree 0 and sort them each round
    int *result = malloc(N * sizeof(int));
    int result_count = 0;

    int zero_nodes[25];
    int zero_count = 0;

    for (int i = 0; i < N; i++) {
        if (in_degree[i] == 0) {
            zero_nodes[zero_count++] = i;
        }
    }

    while (result_count < N) {
        // Sort zero_nodes to pick smallest first
        for (int i = 0; i < zero_count - 1; i++) {
            for (int j = i + 1; j < zero_count; j++) {
                if (zero_nodes[j] < zero_nodes[i]) {
                    int tmp = zero_nodes[i];
                    zero_nodes[i] = zero_nodes[j];
                    zero_nodes[j] = tmp;
                }
            }
        }

        // Pick smallest
        int u = zero_nodes[0];
        result[result_count++] = u;

        // Remove u: decrement in-degree of neighbors
        for (int i = 0; i < count_adj[u]; i++) {
            int v = adj[u + i];
            in_degree[v]--;
            if (in_degree[v] == 0) {
                zero_nodes[zero_count++] = v;
            }
        }

        // Remove used node from zero_nodes (simple shift for small N)
        // We'll just rebuild zero_nodes without u to keep it clean
        int new_zero_count = 0;
        for (int i = 1; i < zero_count; i++) {
            if (i == 1 && zero_nodes[i] != u) {
                // Actually, after picking u=zero_nodes[0], we shift others down
                // But our zero_nodes array is not necessarily contiguous with u at index 0 only
                // Let's just filter out u from the list
            }
        }
        // Simpler: rebuild zero_count without including u
        new_zero_count = 0;
        for (int i = 1; i < zero_count; i++) {
            zero_nodes[new_zero_count++] = zero_nodes[i];
        }
        zero_count = new_zero_count;
    }

    // Check if all nodes included (should be if no cycle)
    if (result_count < N) {
        printf("ERROR\n");
    } else {
        for (int i = 0; i < N; i++) {
            printf("%d%c", result[i], (i == N - 1 ? '\n' : ' '));
        }
    }

    free(adj);
    free(count_adj);
    free(in_degree);
    free(result);
    return 0;
}