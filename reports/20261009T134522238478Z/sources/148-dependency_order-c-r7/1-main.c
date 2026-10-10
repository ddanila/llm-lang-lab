#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) {
        return 0;
    }

    // For N=0, output empty line
    if (N == 0) {
        printf("\n");
        return 0;
    }

    int *in_degree = malloc(N * sizeof(int));
    int **adj = calloc(N, sizeof(int*));
    for (int i = 0; i < N; i++) {
        in_degree[i] = 0;
        adj[i] = NULL;
    }

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (u >= 0 && u < N && v >= 0 && v < N) {
            // Add edge u -> v
            // To handle duplicate edges correctly for lexicographically smallest order,
            // we need to store all edges. Using adjacency list with duplicates.
            int *temp = adj[u];
            adj[u] = malloc((adj[u] ? 1 : 0) + 1);
            adj[u][0] = v;
            if (adj[u]) {
                // Shift existing elements
                for (int j = 1; j < (int)(adj[u] ? (adj[u][0] == v ? 1 : 2) : 0); j++) {
                    adj[u][j] = adj[u][j-1];
                }
            }
            // Actually, let's redo this properly with a simpler approach:
            // Just use a simple adjacency list where we store edges in an array for each node.
            // But reallocating is complex. Let's use a different approach:
            // Store all edges in a flat array and build the graph.
        }
    }

    // Redo with simpler data structure
    free(in_degree);
    free(adj);

    // Use arrays for adjacency
    int **edges = malloc(N * sizeof(int*));
    int *edge_counts = calloc(N, sizeof(int));
    for (int i = 0; i < N; i++) {
        edges[i] = NULL;
        edge_counts[i] = 0;
    }

    // Re-read input? No, we already consumed it. We need to store the graph differently.
    // Let's restart with a cleaner approach: use a single array for all edges and rebuild adjacency.
    // But we can't rewind stdin easily. So we need to handle this in one pass.
    // Actually, let's just use a simple linked list style or dynamic array.
    
    // Better approach: Since N is small (<=20), we can use an adjacency matrix or just store edges.
    // But for topological sort with Kahn's algorithm, we need to know in-degrees and adjacency.
    // Let's use a simple array of arrays for adjacency, resizing as needed.

    int **adj_list = malloc(N * sizeof(int*));
    int *sizes = calloc(N, sizeof(int));
    for (int i = 0; i < N; i++) {
        adj_list[i] = NULL;
        sizes[i] = 0;
    }

    // Re-read M edges
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (u >= 0 && u < N && v >= 0 && v < N) {
            // Add edge u -> v
            int *tmp = adj_list[u];
            sizes[u]++;
            adj_list[u] = malloc(sizes[u] * sizeof(int));
            int pos = 0;
            for (int j = 0; j < sizes[u] - 1; j++) {
                adj_list[u][j] = tmp[j];
            }
            adj_list[u][sizes[u] - 1] = v;
        }
    }

    // Compute in-degrees
    int *in_deg = malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        in_deg[i] = 0;
    }
    for (int u = 0; u < N; u++) {
        for (int j = 0; j < sizes[u]; j++) {
            int v = adj_list[u][j];
            if (v >= 0 && v < N) {
                in_deg[v]++;
            }
        }
    }

    // Kahn's algorithm with a min-heap or just a sorted list since N is small
    // Since we need lexicographically smallest, we can use a priority queue or simply
    // pick the smallest available node at each step.
    
    // Use a simple array for available nodes and sort it each time (N <= 20, so O(N^2) is fine)
    int *available = malloc(N * sizeof(int));
    int avail_count = 0;
    for (int i = 0; i < N; i++) {
        if (in_deg[i] == 0) {
            available[avail_count++] = i;
        }
    }

    int *result = malloc(N * sizeof(int));
    int result_count = 0;

    while (avail_count > 0) {
        // Find the smallest node in available
        int min_idx = 0;
        for (int i = 1; i < avail_count; i++) {
            if (available[i] < available[min_idx]) {
                min_idx = i;
            }
        }
        int u = available[min_idx];
        result[result_count++] = u;

        // Remove u from available
        for (int i = min_idx; i < avail_count - 1; i++) {
            available[i] = available[i + 1];
        }
        avail_count--;

        // Decrease in-degrees of neighbors
        for (int j = 0; j < sizes[u]; j++) {
            int v = adj_list[u][j];
            if (v >= 0 && v < N) {
                in_deg[v]--;
                if (in_deg[v] == 0) {
                    available[avail_count++] = v;
                }
            }
        }
    }

    // Check if all nodes are included (cycle detection)
    if (result_count != N) {
        printf("ERROR\n");
    } else {
        for (int i = 0; i < N; i++) {
            printf("%d%c", result[i], i == N - 1 ? '\n' : ' ');
        }
    }

    free(in_deg);
    free(available);
    free(result);
    free(adj_list);
    free(sizes);
    for (int i = 0; i < N; i++) {
        free(adj_list[i]);
    }

    return 0;
}