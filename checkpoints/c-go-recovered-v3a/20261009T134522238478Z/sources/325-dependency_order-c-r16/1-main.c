#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    // Adjacency list and in-degree array
    int *in_degree = malloc(N * sizeof(int));
    int **adj = malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++) {
        adj[i] = malloc((N + M) * sizeof(int)); // Max edges per node is bounded by M+N in worst case
        adj[i][0] = -1;
        in_degree[i] = 0;
    }

    int edge_count = 0;

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (u >= N || v >= N) continue; // Should not happen per spec
        // Add edge u -> v
        int *edge = adj[u];
        while (*edge != -1 && *edge != v) {
            edge++;
        }
        if (*edge == -1) {
            *edge++ = v;
        }
        // Skip duplicates by checking existing edges
        // But we need to track in_degree only once per unique edge
        // We'll handle duplicate edges by not incrementing in_degree if already exists
        int found = 0;
        edge = adj[u];
        while (*edge != -1) {
            if (*edge == v) {
                found = 1;
                break;
            }
            edge++;
        }
        if (!found) {
            // Need to insert or append? Let's use a simpler approach: just store all and filter later
            // Actually, let's rebuild adj with duplicates and handle during topo sort
            // But for correctness, we need unique edges. Let's do it properly.
        }
    }

    // Re-read edges and build proper graph with unique edges only
    // Reset in_degree and adj
    free(in_degree);
    free(adj);
    in_degree = malloc(N * sizeof(int));
    adj = malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++) {
        adj[i] = malloc((N + M) * sizeof(int));
        adj[i][0] = -1;
        in_degree[i] = 0;
    }

    edge_count = 0;
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (u >= N || v >= N) continue;
        
        // Check if edge u->v already exists
        int *e = adj[u];
        while (*e != -1) {
            if (*e == v) break;
            e++;
        }
        if (*e != v) {
            // Add edge
            int pos = 0;
            while (adj[u][pos] != -1) pos++;
            adj[u][pos] = v;
            in_degree[v]++;
        }
    }

    // Kahn's algorithm with min-heap priority queue for lexicographically smallest order
    // Since N <= 20, we can use a simple array and scan for min each time
    
    int *result = malloc(N * sizeof(int));
    int result_idx = 0;
    
    // Count nodes with in_degree 0
    int zero_count = 0;
    for (int i = 0; i < N; i++) {
        if (in_degree[i] == 0) {
            zero_count++;
        }
    }
    
    // We'll maintain a list of available nodes and pick the smallest each time
    int *available = malloc(N * sizeof(int));
    int avail_idx = 0;
    for (int i = 0; i < N; i++) {
        if (in_degree[i] == 0) {
            available[avail_idx++] = i;
        }
    }
    
    // While there are nodes in available list
    while (avail_idx > 0) {
        // Find minimum node index
        int min_node = available[0];
        for (int i = 1; i < avail_idx; i++) {
            if (available[i] < min_node) {
                min_node = available[i];
            }
        }
        
        // Remove min_node from available list
        int removed = 0;
        for (int i = 0; i < avail_idx; i++) {
            if (available[i] == min_node) {
                removed = 1;
                break;
            }
        }
        // Actually, let's rebuild without the min node
        int new_avail[20];
        int new_idx = 0;
        for (int i = 0; i < avail_idx; i++) {
            if (available[i] != min_node) {
                new_avail[new_idx++] = available[i];
            }
        }
        // Copy back
        for (int i = 0; i < new_idx; i++) {
            available[i] = new_avail[i];
        }
        avail_idx = new_idx;
        
        result[result_idx++] = min_node;
        
        // Decrease in_degree of neighbors
        int *neighbors = adj[min_node];
        while (*neighbors != -1) {
            int v = *neighbors;
            in_degree[v]--;
            if (in_degree[v] == 0) {
                available[avail_idx++] = v;
            }
            neighbors++;
        }
    }
    
    // Check if all nodes are included (i.e., no cycle)
    if (result_idx < N) {
        printf("ERROR\n");
    } else {
        for (int i = 0; i < N; i++) {
            printf("%d%c", result[i], (i == N-1 ? '\n' : ' '));
        }
    }

    free(in_degree);
    free(adj);
    free(result);
    free(available);
    
    return 0;
}