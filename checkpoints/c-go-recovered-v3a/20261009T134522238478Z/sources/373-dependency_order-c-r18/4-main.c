#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    // Adjacency list using linked lists for each node
    int *head = NULL;
    int *next_edge = NULL;
    int *edge_to = NULL;
    
    if (N > 0 && M > 0) {
        head = calloc(N, sizeof(int));
        next_edge = malloc(M * sizeof(int));
        edge_to = malloc(M * sizeof(int));
        memset(head, -1, N * sizeof(int));
        
        for (int i = 0; i < M; i++) {
            int u, v;
            scanf("%d %d", &u, &v);
            // Insert edge at front of linked list
            next_edge[i] = head[u];
            edge_to[i] = v;
            head[u] = i;
        }
    }

    // Compute initial indegrees
    int *indegree = NULL;
    if (N > 0) {
        indegree = calloc(N, sizeof(int));
        
        for (int u = 0; u < N; u++) {
            for (int e = head[u]; e != -1; e = next_edge[e]) {
                int v = edge_to[e];
                if (v >= 0 && v < N) {
                    indegree[v]++;
                }
            }
        }
    }

    // Kahn's algorithm with selection of minimum index node among those with indegree 0
    int *result = NULL;
    int result_idx = 0;
    
    if (N > 0) {
        result = malloc(N * sizeof(int));
        
        while (result_idx < N) {
            // Find the smallest index node with indegree 0
            int best = -1;
            for (int i = 0; i < N; i++) {
                if (indegree[i] == 0 && (best == -1 || i < best)) {
                    best = i;
                }
            }
            
            if (best == -1) {
                // Cycle detected
                printf("ERROR\n");
                free(head);
                free(next_edge);
                free(edge_to);
                free(indegree);
                free(result);
                return 0;
            }
            
            result[result_idx++] = best;
            
            // Decrease indegree of neighbors
            for (int e = head[best]; e != -1; e = next_edge[e]) {
                int v = edge_to[e];
                if (v >= 0 && v < N) {
                    indegree[v]--;
                }
            }
        }
    }

    if (N > 0) {
        for (int i = 0; i < N; i++) {
            printf("%d", result[i]);
            if (i < N - 1) printf(" ");
        }
        printf("\n");
    } else {
        // N=0 case: empty output
        printf("\n");
    }

    free(head);
    free(next_edge);
    free(edge_to);
    free(indegree);
    free(result);

    return 0;
}