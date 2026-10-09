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

    // Use adjacency matrix for simplicity with N <= 20
    int adj[20][20];
    memset(adj, 0, sizeof(adj));
    
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u][v]++;  // Allow duplicate edges
    }

    // In-degree array
    int indegree[20];
    for (int i = 0; i < N; i++) {
        indegree[i] = 0;
        for (int j = 0; j < N; j++) {
            if (adj[i][j]) {
                indegree[j] += adj[i][j];
            }
        }
    }

    // Use a simple array as priority queue with linear scan
    int *pq = malloc(N * sizeof(int));
    int pq_size = 0;
    
    for (int i = 0; i < N; i++) {
        if (indegree[i] == 0) {
            pq[pq_size++] = i;
        }
    }

    // Keep sorted
    while (pq_size > 1) {
        for (int i = 0; i < pq_size - 1; i++) {
            if (pq[i + 1] < pq[i]) {
                int tmp = pq[i];
                pq[i] = pq[i + 1];
                pq[i + 1] = tmp;
            }
        }
    }

    int result_count = 0;
    int *result = malloc(N * sizeof(int));

    while (pq_size > 0) {
        // Take smallest
        int u = pq[0];
        for (int i = 1; i < pq_size; i++) {
            if (pq[i] < pq[0]) {
                int tmp = pq[0];
                pq[0] = pq[i];
                pq[i] = tmp;
            } else {
                break;
            }
        }
        
        result[result_count++] = u;

        // Remove from front
        for (int i = 1; i < pq_size; i++) {
            pq[i - 1] = pq[i];
        }
        pq_size--;

        // Update neighbors
        for (int v = 0; v < N; v++) {
            if (adj[u][v]) {
                indegree[v] -= adj[u][v];
                if (indegree[v] == 0) {
                    // Insert into sorted position
                    int pos = pq_size;
                    while (pos > 0 && pq[pos - 1] > v) {
                        pq[pos] = pq[pos - 1];
                        pos--;
                    }
                    pq[pos] = v;
                    pq_size++;
                }
            }
        }
    }

    if (result_count != N) {
        printf("ERROR\n");
    } else {
        for (int i = 0; i < N; i++) {
            printf("%d%c", result[i], (i == N - 1 ? '\n' : ' '));
        }
    }

    free(pq);
    free(result);

    return 0;
}