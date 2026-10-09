#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    // Adjacency matrix for simplicity (N <= 20)
    int adj[20][20];
    int in_degree[20];
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            adj[i][j] = 0;
        }
        in_degree[i] = 0;
    }
    
    // Read M edges
    for (int k = 0; k < M; k++) {
        int u, v;
        scanf("%d %d", &u, &v);
        
        // Add edge u -> v
        if (adj[u][v] == 0) {
            adj[u][v] = 1;
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
    
    // Sort the initial queue using bubble sort
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
        
        // Process neighbors in sorted order
        for (int v = 0; v < N; v++) {
            if (adj[u][v] && in_degree[v] > 0) {
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
            }
        }
    }
    
    // Check for cycle
    if (result_count < N) {
        printf("ERROR\n");
    } else {
        printf("\n");
    }
    
    free(queue);
    
    return 0;
}