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

    // Adjacency list using arrays for edges
    int *head = malloc(N * sizeof(int));
    int *next = calloc(M, sizeof(int));
    int *to = calloc(M, sizeof(int));
    int edge_count = 0;

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        to[edge_count] = v;
        next[edge_count] = head[u];
        head[u] = edge_count++;
    }

    // In-degree array
    int *indegree = calloc(N, sizeof(int));
    for (int i = 0; i < N; i++) {
        for (int e = head[i]; e != -1; e = next[e]) {
            indegree[to[e]]++;
        }
    }

    // Priority queue simulation using a sorted array of nodes with indegree 0
    int *pq = malloc(N * sizeof(int));
    int pq_size = 0;
    for (int i = 0; i < N; i++) {
        if (indegree[i] == 0) {
            pq[pq_size++] = i;
        }
    }

    // Keep pq sorted at all times
    for (int i = 0; i < pq_size - 1; i++) {
        for (int j = i + 1; j < pq_size; j++) {
            if (pq[j] < pq[i]) {
                int temp = pq[i];
                pq[i] = pq[j];
                pq[j] = temp;
            }
        }
    }

    int result_count = 0;
    int *result = malloc(N * sizeof(int));

    while (pq_size > 0) {
        // Take the smallest element from pq
        int u = pq[0];
        for (int i = 1; i < pq_size; i++) {
            if (pq[i] < pq[0]) {
                int temp = pq[0];
                pq[0] = pq[i];
                pq[i] = temp;
            } else {
                break;
            }
        }
        result[result_count++] = u;

        // Remove from pq by shifting
        for (int i = 0; i < pq_size - 1; i++) {
            pq[i] = pq[i + 1];
        }
        pq_size--;

        // Update indegrees and add new nodes to pq
        for (int e = head[u]; e != -1; e = next[e]) {
            int v = to[e];
            if (--indegree[v] == 0) {
                // Insert into sorted position
                int idx = pq_size;
                while (idx > 0 && v < pq[idx - 1]) {
                    pq[idx] = pq[idx - 1];
                    idx--;
                }
                pq[idx] = v;
                pq_size++;
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

    free(head);
    free(next);
    free(to);
    free(indegree);
    free(pq);
    free(result);

    return 0;
}