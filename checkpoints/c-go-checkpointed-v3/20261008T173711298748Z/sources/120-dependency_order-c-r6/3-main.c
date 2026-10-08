#include <stdio.h>
#include <stdlib.h>

typedef struct Edge {
    int v;
    struct Edge *next;
} Edge;

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    // For N=0, output empty line
    if (N == 0) {
        printf("\n");
        return 0;
    }

    Edge **adj = malloc(N * sizeof(Edge*));
    int *in_degree = calloc(N, sizeof(int));
    
    for (int i = 0; i < N; i++) {
        adj[i] = NULL;
    }

    // Read edges
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        // Handle self-loops: ignore them for topological sort purposes
        if (u != v) {
            Edge *e = malloc(sizeof(Edge));
            e->v = v;
            e->next = adj[u];
            adj[u] = e;
            in_degree[v]++;
        }
    }

    // Kahn's algorithm with linear scan to find smallest available node
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
            for (int i = 0; i < N; i++) {
                Edge *e = adj[i];
                while (e != NULL) {
                    Edge *temp = e;
                    e = e->next;
                    free(temp);
                }
            }
            free(adj);
            free(in_degree);
            free(result);
            return 0;
        }

        result[result_idx++] = best_node;
        count++;
        
        // Decrease in_degree of neighbors (keep edges for now, don't free)
        Edge *e = adj[best_node];
        while (e != NULL) {
            int v = e->v;
            in_degree[v]--;
            Edge *temp = e;
            e = e->next;
            free(temp);  // Free after processing to avoid memory issues
        }
        adj[best_node] = NULL;
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