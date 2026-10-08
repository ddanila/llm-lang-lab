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

    int *adj = NULL;
    int *in_degree = NULL;
    int edge_count = 0;
    
    // Read edges
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (adj == NULL) {
            adj = malloc(N * sizeof(int));
            in_degree = calloc(N, sizeof(int));
        }
        // Handle self-loops: ignore for topological sort (cycle detection will handle them)
        if (u != v) {
            adj[u] = v;
            edge_count++;
            in_degree[v]++;
        }
    }

    // Kahn's algorithm with priority queue simulation using a simple array and linear scan
    // to find the smallest available node at each step.
    
    int *result = malloc(N * sizeof(int));
    int result_idx = 0;
    int count = 0;

    while (count < N) {
        int best_node = -1;
        
        // Find the node with in_degree 0 that is smallest
        for (int i = 0; i < N; i++) {
            if (in_degree[i] == 0) {
                if (best_node == -1 || i < best_node) {
                    best_node = i;
                }
            }
        }

        if (best_node == -1) {
            // No node with in_degree 0, but we haven't processed all nodes -> cycle
            printf("ERROR\n");
            free(adj);
            free(in_degree);
            free(result);
            return 0;
        }

        result[result_idx++] = best_node;
        count++;
        
        // Decrease in_degree of neighbors
        if (adj[best_node] != -1) {
            int v = adj[best_node];
            in_degree[v]--;
        }
    }

    // Output result
    for (int i = 0; i < N; i++) {
        printf("%d", result[i]);
        if (i < N - 1) printf(" ");
    }
    printf("\n");

    free(adj);
    free(in_degree);
    free(result);
    
    return 0;
}