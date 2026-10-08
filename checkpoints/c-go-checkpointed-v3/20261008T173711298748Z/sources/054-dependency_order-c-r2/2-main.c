#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    // Adjacency list using linked lists for edges
    int *head = calloc(N, sizeof(int));
    int *to = malloc(M * sizeof(int));
    int *next = malloc(M * sizeof(int));
    int edge_count = 0;
    
    int *in_degree = calloc(N, sizeof(int));
    
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        
        // Add edge u -> v (allow duplicates by processing each)
        int new_edge = edge_count++;
        to[new_edge] = v;
        next[new_edge] = head[u];
        head[u] = new_edge;
        in_degree[v]++;
    }
    
    // For lexicographically smallest topological sort
    int *output = calloc(N, sizeof(int));
    int result_count = 0;
    int remaining = N;
    
    while (remaining > 0) {
        int best_node = -1;
        for (int i = 0; i < N; i++) {
            if (!output[i] && in_degree[i] == 0) {
                if (best_node == -1 || i < best_node) {
                    best_node = i;
                }
            }
        }
        
        if (best_node == -1) {
            // Cycle detected
            printf("ERROR\n");
            free(head);
            free(to);
            free(next);
            free(in_degree);
            free(output);
            return 0;
        }
        
        result_count++;
        output[best_node] = 1;
        remaining--;
        
        // Decrease in_degree of neighbors
        int temp = head[best_node];
        while (temp != -1) {
            int v = to[temp];
            in_degree[v]--;
            temp = next[temp];
        }
    }
    
    // Output result
    for (int i = 0; i < N; i++) {
        printf("%d%c", i, i == N - 1 ? '\n' : ' ');
    }
    
    free(head);
    free(to);
    free(next);
    free(in_degree);
    free(output);
    
    return 0;
}