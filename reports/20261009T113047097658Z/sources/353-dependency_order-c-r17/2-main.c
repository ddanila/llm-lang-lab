#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    // In-degree count
    int *indegree = calloc(N, sizeof(int));
    if (!indegree) return 1;

    // Adjacency list: for each node, store next edge index
    int *head = calloc(N, sizeof(int));
    int *next = malloc(M * sizeof(int));
    if (!head || !next) {
        free(head);
        free(next);
        free(indegree);
        return 1;
    }

    // Initialize head to -1
    memset(head, -1, N * sizeof(int));

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        
        next[i] = head[u];
        head[u] = i;
        indegree[v]++;
    }

    free(next);

    // Kahn's algorithm with priority queue simulation
    int *result = malloc(N * sizeof(int));
    if (!result) {
        free(head);
        free(indegree);
        return 1;
    }

    int count = 0;
    
    for (int step = 0; step < N; step++) {
        int best_node = -1;
        
        // Find the smallest node with indegree 0
        for (int j = 0; j < N; j++) {
            if (indegree[j] == 0) {
                if (best_node == -1 || j < best_node) {
                    best_node = j;
                }
            }
        }
        
        if (best_node == -1) {
            break; // Cycle detected
        }
        
        result[count++] = best_node;
        indegree[best_node] = -1; // Mark as processed
        
        // Update neighbors
        for (int e = head[best_node]; e != -1; e = next[e]) {
            int v = 0;
            // Need to store targets separately since we only have edge indices
            // Actually, we need to restructure: store target in a parallel array
            break;
        }
    }
    
    // We need to store targets. Let me fix this properly.
    free(head);
    free(indegree);
    
    indegree = calloc(N, sizeof(int));
    head = calloc(N, sizeof(int));
    next = malloc(M * sizeof(int));
    int *targets = malloc(M * sizeof(int));
    if (!indegree || !head || !next || !targets) {
        free(head);
        free(indegree);
        free(next);
        free(targets);
        return 1;
    }
    
    memset(head, -1, N * sizeof(int));

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        
        next[i] = head[u];
        head[u] = i;
        targets[i] = v;
        indegree[v]++;
    }

    // Kahn's algorithm
    count = 0;
    
    for (int step = 0; step < N; step++) {
        int best_node = -1;
        
        // Find the smallest node with indegree 0
        for (int j = 0; j < N; j++) {
            if (indegree[j] == 0) {
                if (best_node == -1 || j < best_node) {
                    best_node = j;
                }
            }
        }
        
        if (best_node == -1) {
            break; // Cycle detected
        }
        
        result[count++] = best_node;
        indegree[best_node] = -1; // Mark as processed
        
        // Update neighbors
        for (int e = head[best_node]; e != -1; e = next[e]) {
            int v = targets[e];
            if (indegree[v] > 0) {
                indegree[v]--;
            }
        }
    }

    if (count < N) {
        printf("ERROR\n");
    } else {
        for (int i = 0; i < N; i++) {
            if (i > 0) printf(" ");
            printf("%d", result[i]);
        }
        printf("\n");
    }

    free(result);
    free(head);
    free(indegree);
    free(next);
    free(targets);
    
    return 0;
}