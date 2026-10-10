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
    
    if (N > 0) {
        head = calloc(N, sizeof(int));
        next_edge = malloc(M * sizeof(int));
        edge_to = malloc(M * sizeof(int));
        memset(head, -1, N * sizeof(int));
        
        for (int i = 0; i < M; i++) {
            int u, v;
            scanf("%d %d", &u, &v);
            // Store edge: head[u] points to first edge from u
            // We'll insert at the front for simplicity, but need to maintain order for lex smallest
            // Actually, for Kahn's algorithm with priority queue, order of edges doesn't matter
            // as long as we process nodes in order. But we need to output lex smallest ordering.
            
            // For lex smallest topological sort, we use a min-heap (priority queue) for Kahn's
            // But since N <= 20, we can just use an array and scan for minimum indegree 0 node
            
            // Insert edge at front of linked list
            next_edge[i] = head[u];
            edge_to[i] = v;
            head[u] = i;
        }
    }

    // Compute initial indegrees
    int *indegree = malloc(N > 0 ? N * sizeof(int) : 1);
    if (N > 0) {
        memset(indegree, 0, N * sizeof(int));
        
        for (int i = 0; i < M; i++) {
            int v = edge_to[i];
            indegree[v]++;
        }
    }

    // Kahn's algorithm with selection of minimum index node among those with indegree 0
    int *result = malloc(N > 0 ? N * sizeof(int) : 1);
    int result_idx = 0;

    while (result_idx < N) {
        if (N > 0) {
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
                indegree[v]--;
            }
        } else {
            break;
        }
    }

    if (result_idx < N) {
        // Cycle detected (shouldn't happen with the above logic, but for safety)
        printf("ERROR\n");
    } else {
        for (int i = 0; i < N; i++) {
            printf("%d", result[i]);
            if (i < N - 1) printf(" ");
        }
        printf("\n");
    }

    free(head);
    free(next_edge);
    free(edge_to);
    free(indegree);
    free(result);

    return 0;
}