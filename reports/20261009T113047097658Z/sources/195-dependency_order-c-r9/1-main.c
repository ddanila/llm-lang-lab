#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    // Adjacency list: adj[u] contains v
    int *adj = NULL;
    int *indegree = NULL;
    int *adj_count = NULL;
    int adj_cap = 0;
    int indegree_cap = N + 1;
    int adj_cnt[N];

    // Initialize adjacency structures
    if (N > 0) {
        adj_cap = M + 1;
        adj = malloc(adj_cap * sizeof(int));
        adj_count = malloc(N * sizeof(int));
        indegree = calloc(N, sizeof(int));
        for (int i = 0; i < N; i++) adj_count[i] = 0;

        for (int i = 0; i < M; i++) {
            int u, v;
            scanf("%d %d", &u, &v);
            if (u >= 0 && u < N && v >= 0 && v < N) {
                // Add edge u -> v
                if (adj_count[u] < adj_cap) {
                    adj[adj_count[u]] = v;
                    adj_count[u]++;
                } else {
                    // Resize adjacency list
                    int new_cap = adj_cap * 2 + 1;
                    int *new_adj = realloc(adj, new_cap * sizeof(int));
                    if (!new_adj) break;
                    adj = new_adj;
                    for (int k = 0; k < adj_count[u]; k++) {
                        new_adj[adj_count[u] + k] = v; // duplicate edges allowed
                    }
                    adj_cap = new_cap;
                    adj[adj_count[u]] = v;
                    adj_count[u]++;
                }
                indegree[v]++;
            }
        }
    }

    // Kahn's algorithm with priority queue (min-heap) to get lexicographically smallest ordering
    // Since we need lexicographically smallest, at each step we pick the smallest available node.
    // We can use a simple array and linear scan since N <= 20.

    int *order = NULL;
    if (N > 0) {
        order = malloc(N * sizeof(int));
    }

    int idx = 0;
    while (idx < N) {
        int best_node = -1;
        for (int i = 0; i < N; i++) {
            if (indegree[i] == 0) {
                best_node = i;
                break; // Since we scan from 0 to N-1, the first one is smallest
            }
        }

        if (best_node == -1) {
            // Cycle detected
            free(adj);
            free(indegree);
            free(adj_count);
            free(order);
            printf("ERROR\n");
            return 0;
        }

        order[idx] = best_node;
        indegree[best_node] = -1; // Mark as processed

        // Update neighbors
        for (int k = 0; k < adj_count[best_node]; k++) {
            int v = adj[k];
            if (indegree[v] > 0) {
                indegree[v]--;
            }
        }
        idx++;
    }

    // Output result
    for (int i = 0; i < N; i++) {
        printf("%d", order[i]);
        if (i < N - 1) printf(" ");
    }
    printf("\n");

    free(adj);
    free(indegree);
    free(adj_count);
    free(order);

    return 0;
}