#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    // Adjacency list and in-degree count
    int *adj = NULL;
    int *in_degree = calloc(N, sizeof(int));
    int edge_count[N];
    
    if (N > 0) {
        adj = malloc(N * sizeof(int *));
        for (int i = 0; i < N; i++) {
            adj[i] = NULL;
            edge_count[i] = 0;
        }
        
        // Read M edges
        for (int k = 0; k < M; k++) {
            int u, v;
            scanf("%d %d", &u, &v);
            
            // Add edge u -> v
            if (adj[u] == NULL) {
                adj[u] = malloc((edge_count[u] + 2) * sizeof(int));
            } else {
                int current = adj[u];
                while (current != NULL && *current != v) {
                    current = *(current + 1);
                }
                if (*current != v) {
                    // Need to add v - find insertion point
                    int i = 0;
                    while (adj[u][i] != v) i++;
                    // Insert at position i
                    for (int j = edge_count[u]; j > i; j--) {
                        adj[u][j] = adj[u][j-1];
                    }
                    adj[u][i] = v;
                }
            }
            in_degree[v]++;
            edge_count[u]++;
        }
    }

    // Kahn's algorithm with priority queue simulation using a sorted array
    // We need to repeatedly pick the smallest node with in-degree 0
    
    int *queue = malloc(N * sizeof(int));
    int head = 0;
    int tail = 0;
    
    // Initialize queue with all nodes having in-degree 0
    for (int i = 0; i < N; i++) {
        if (in_degree[i] == 0) {
            queue[tail++] = i;
        }
    }
    
    // Sort the initial queue to get lexicographically smallest order
    // Since we need smallest at each step, we'll maintain sorted order
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
        
        // For each neighbor v of u, decrement in_degree
        if (adj[u] != NULL) {
            int *ptr = adj[u];
            while (*ptr != -1) {
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
                ptr++;
            }
        }
    }
    
    // Check for cycle: if we didn't process all nodes
    if (result_count < N) {
        printf("ERROR\n");
    }
    
    free(adj);
    free(in_degree);
    free(queue);
    
    return 0;
}