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

    int **adj = malloc(N * sizeof(int*));
    int *in_degree = calloc(N, sizeof(int));
    
    for (int i = 0; i < N; i++) {
        adj[i] = NULL;
    }

    // Read edges - use a simple adjacency list with arrays
    // For each node, store list of neighbors in adj[node]
    // We'll use linked lists via separate allocation
    
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (u != v) {
            Edge *e = malloc(sizeof(Edge));
            e->v = v;
            e->next = adj[u];
            adj[u] = e;
            in_degree[v]++;
        }
    }

    // Actually, let me simplify - just use a single array for all edges
    // and process them properly
    
    printf("DEBUG: N=%d M=%d\n", N, M);
    
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

        printf("DEBUG: best_node=%d\n", best_node);

        if (best_node == -1) {
            printf("ERROR\n");
            return 0;
        }

        result[result_idx++] = best_node;
        count++;
        
        // Decrease in_degree of neighbors
        Edge *e = adj[best_node];
        while (e != NULL) {
            int v = e->v;
            in_degree[v]--;
            Edge *temp = e;
            e = e->next;
            free(temp);
        }
        adj[best_node] = NULL;
    }

    // Output result
    for (int i = 0; i < N; i++) {
        printf("%d", result[i]);
        if (i < N - 1) printf(" ");
    }
    printf("\n");

    return 0;
}

typedef struct Edge {
    int v;
    struct Edge *next;
} Edge;