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

    // Use simpler arrays
    int *head = malloc(N * sizeof(int));
    int *next = calloc(M, sizeof(int));
    int *to = calloc(M, sizeof(int));
    
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        to[i] = v;
        next[i] = head[u];
        head[u] = i;
    }

    // In-degree array
    int *indegree = calloc(N, sizeof(int));
    for (int i = 0; i < N; i++) {
        for (int e = head[i]; e != -1; e = next[e]) {
            indegree[to[e]]++;
        }
    }

    // Simple min-heap using an array
    int *heap = malloc(N * sizeof(int));
    int heap_size = 0;
    
    for (int i = 0; i < N; i++) {
        if (indegree[i] == 0) {
            heap[heap_size++] = i;
        }
    }

    // Build heap
    for (int i = heap_size / 2 - 1; i >= 0; i--) {
        int temp = heap[i];
        int child = 2 * i + 1;
        while (child < heap_size) {
            if (child + 1 < heap_size && heap[child + 1] < heap[child]) {
                child++;
            }
            if (heap[child] < temp) {
                heap[i] = heap[child];
                child = 2 * child + 1;
            } else {
                break;
            }
        }
        heap[i] = temp;
    }

    int result_count = 0;
    int *result = malloc(N * sizeof(int));

    while (heap_size > 0) {
        // Extract min
        int u = heap[0];
        heap[0] = heap[--heap_size];
        
        // Heapify down
        int temp = heap[0];
        int child = 0;
        while (child * 2 + 1 < heap_size) {
            int left = child * 2 + 1;
            int right = left + 1;
            if (right < heap_size && heap[right] < heap[left]) {
                left = right;
            }
            if (heap[left] < temp) {
                heap[child] = heap[left];
                child = left;
            } else {
                break;
            }
        }
        heap[child] = temp;

        result[result_count++] = u;

        // Process neighbors
        for (int e = head[u]; e != -1; e = next[e]) {
            int v = to[e];
            if (--indegree[v] == 0) {
                heap[heap_size++] = v;
                // Heapify up
                int idx = heap_size - 1;
                while (idx > 0) {
                    int parent = (idx - 1) / 2;
                    if (heap[parent] < heap[idx]) {
                        break;
                    }
                    heap[idx] = heap[parent];
                    idx = parent;
                }
                heap[idx] = v;
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
    free(heap);
    free(result);

    return 0;
}