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

    // Adjacency list using arrays
    int *head = calloc(N, sizeof(int));
    int *next = calloc(M, sizeof(int));
    int *to = calloc(M, sizeof(int));
    memset(head, -1, N * sizeof(int));

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        // Edge u -> v: u must precede v
        to[i] = v;
        next[i] = head[u];
        head[u] = i;
    }

    // In-degree array
    int *indegree = calloc(N, sizeof(int));
    for (int i = 0; i < M; i++) {
        indegree[to[i]]++;
    }

    // Priority queue: min-heap based on node index
    // We'll use a simple array-based heap since N is small (<=20)
    int *pq = calloc(N, sizeof(int));
    int pq_size = 0;

    // Add all nodes with indegree 0 to the priority queue
    for (int i = 0; i < N; i++) {
        if (indegree[i] == 0) {
            pq[pq_size++] = i;
        }
    }

    int *result = calloc(N, sizeof(int));
    int result_count = 0;

    // Heap operations
    #define SWAP(a,b) do { int t=a; a=b; b=t; } while(0)

    while (pq_size > 0) {
        // Find min element in heap (indices 0 to pq_size-1)
        int min_idx = 0;
        for (int i = 1; i < pq_size; i++) {
            if (pq[i] < pq[min_idx]) {
                min_idx = i;
            }
        }

        // Extract min
        int extracted = pq[min_idx];
        pq[min_idx] = pq[pq_size - 1];
        pq_size--;

        result[result_count++] = extracted;

        // Process neighbors of extracted node
        for (int e = head[extracted]; e != -1; e = next[e]) {
            int v = to[e];
            indegree[v]--;
            if (indegree[v] == 0) {
                pq[pq_size++] = v;
            }
        }
    }

    // Check if all nodes were processed (cycle detection)
    if (result_count != N) {
        printf("ERROR\n");
    } else {
        for (int i = 0; i < N; i++) {
            printf("%d", result[i]);
            if (i < N - 1) printf(" ");
        }
        printf("\n");
    }

    free(head);
    free(next);
    free(to);
    free(indegree);
    free(pq);
    free(result);

    return 0;
}