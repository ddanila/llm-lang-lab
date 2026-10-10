#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    // For N=0, output empty line
    if (N == 0) {
        printf("\n");
        return 0;
    }

    int *in_degree = malloc(N * sizeof(int));
    int **adj = malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++) {
        adj[i] = malloc((N + M + 1) * sizeof(int));
        adj[i][0] = -1;
        in_degree[i] = 0;
    }

    int edge_count = 0;
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (u < 0 || u >= N || v < 0 || v >= N) continue;
        
        // Check if edge already exists
        int *e = adj[u];
        while (*e != -1 && *e != v) {
            e++;
        }
        if (*e != v) {
            // Add edge u->v
            int pos = 0;
            while (adj[u][pos] != -1) pos++;
            adj[u][pos] = v;
            in_degree[v]++;
            edge_count++;
        }
    }

    // Kahn's algorithm with lexicographically smallest order
    int *result = malloc(N * sizeof(int));
    int result_idx = 0;
    
    // Count zero in-degree nodes and add to available list
    int *available = malloc(N * sizeof(int));
    int avail_count = 0;
    for (int i = 0; i < N; i++) {
        if (in_degree[i] == 0) {
            available[avail_count++] = i;
        }
    }
    
    while (avail_count > 0) {
        // Find minimum node index in available list
        int min_node = available[0];
        for (int i = 1; i < avail_count; i++) {
            if (available[i] < min_node) {
                min_node = available[i];
            }
        }
        
        // Remove min_node from available list by shifting
        for (int i = 0; i < avail_count - 1; i++) {
            available[i] = available[i + 1];
        }
        avail_count--;
        
        result[result_idx++] = min_node;
        
        // Process neighbors of min_node
        int *neighbors = adj[min_node];
        while (*neighbors != -1) {
            int v = *neighbors;
            in_degree[v]--;
            if (in_degree[v] == 0) {
                available[avail_count++] = v;
            }
            neighbors++;
        }
    }
    
    // Check if cycle exists
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