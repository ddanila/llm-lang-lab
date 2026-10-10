#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    // Adjacency list using array of linked lists
    // adj[u] points to first edge from u
    int *adj = NULL;
    int *in_degree = calloc(N, sizeof(int));
    
    if (N > 0) {
        adj = malloc(N * sizeof(int *));
        for (int i = 0; i < N; i++) {
            adj[i] = NULL;
        }
        
        // Read M edges
        for (int k = 0; k < M; k++) {
            int u, v;
            scanf("%d %d", &u, &v);
            
            // Add edge u -> v
            if (adj[u] == NULL) {
                adj[u] = malloc(sizeof(int));
                *adj[u] = v;
            } else {
                int current = adj[u];
                while (*current != -1 && *current != v) {
                    current = *(current + 1);
                }
                if (*current == -1 || *current != v) {
                    // Insert v (maintain sorted order for determinism, but any order works)
                    int i = 0;
                    while (adj[u][i] != -1 && adj[u][i] < v) i++;
                    
                    // Make space for insertion
                    int *new_adj = realloc(adj[u], sizeof(int) * (i + 2));
                    if (!new_adj) break;
                    adj[u] = new_adj;
                    
                    for (int j = edge_count[u]; j > i; j--) {
                        adj[u][j] = adj[u][j-1];
                    }
                    adj[u][i] = v;
                }
            }
            in_degree[v]++;
        }
    }

    // Kahn's algorithm with sorted queue
    int *queue = malloc(N * sizeof(int));
    int head = 0;
    int tail = 0;
    
    // Initialize queue with all nodes having in-degree 0
    for (int i = 0; i < N; i++) {
        if (in_degree[i] == 0) {
            queue[tail++] = i;
        }
    }
    
    // Sort the initial queue
    for (int i = 0; i < tail - 1; i++) {
        for (int j = tail - 1; j > i; j--) {
            if (queue[j] > queue[j-1]) {
                int temp = queue[j];
                queue[j] = queue[j-1];
                queue[j-1] = temp;
            }
        }
    }
    
    int result_count = 0;
    while (head < tail) {
        int u = queue[head++];
        printf("%d%c", u, result_count == N - 1 ? '\n' : ' ');
        result_count++;
        
        // Process neighbors
        int *ptr = adj[u];
        while (ptr != NULL && *ptr != -1) {
            int v = *ptr;
            in_degree[v]--;
            if (in_degree[v] == 0) {
                // Insert v into queue in sorted order
                int pos = tail;
                for (int i = head; i < tail; i++) {
                    if (v < queue[i]) {
                        pos = i;
                        break;
                    }
                }
                for (int j = tail - 1; j > pos; j--) {
                    queue[j + 1] = queue[j];
                }
                queue[pos] = v;
                tail++;
            }
            ptr = *(ptr + 1);
        }
    }
    
    // Check for cycle
    if (result_count < N) {
        printf("ERROR\n");
    } else {
        printf("\n");
    }
    
    free(adj);
    free(in_degree);
    free(queue);
    
    return 0;
}