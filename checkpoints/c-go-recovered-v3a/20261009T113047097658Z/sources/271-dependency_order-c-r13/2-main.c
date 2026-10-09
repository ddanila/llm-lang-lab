#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    if (N == 0) {
        printf("\n");
        return 0;
    }

    // Adjacency list: head[u] -> first edge index
    int *head = malloc(N * sizeof(int));
    int indegree[N];
    memset(indegree, 0, sizeof(indegree));
    
    for (int i = 0; i < N; i++) head[i] = -1;
    
    // Store edges as linked lists: next_edge[e] points to next edge from same source
    int *next_edge = malloc(M * sizeof(int));
    int edge_from[M], edge_to[M];

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (u >= N || v >= N) continue; // Should not happen based on spec
        
        edge_from[i] = u;
        edge_to[i] = v;
        next_edge[i] = head[u];
        head[u] = i;
        
        indegree[v]++;
    }

    // Kahn's algorithm with priority to smallest node first
    int *order = malloc(N * sizeof(int));
    int count = 0;

    while (count < N) {
        int best = -1;
        for (int i = 0; i < N; i++) {
            if (indegree[i] == 0 && best == -1) {
                best = i;
            } else if (indegree[i] == 0 && best != -1) {
                if (i < best) best = i;
            }
        }

        if (best == -1) {
            // No node with indegree 0, cycle detected
            printf("ERROR\n");
            free(head);
            free(next_edge);
            free(order);
            return 0;
        }

        order[count++] = best;
        
        // Remove edges from best and update indegrees
        for (int e = head[best]; e != -1; e = next_edge[e]) {
            int v = edge_to[e];
            indegree[v]--;
        }
    }

    for (int i = 0; i < N; i++) {
        printf("%d%c", order[i], (i == N-1) ? '\n' : ' ');
    }

    free(head);
    free(next_edge);
    free(order);

    return 0;
}