#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    // For N=0, output empty line
    if (N == 0) {
        printf("\n");
        return 0;
    }

    int *head = malloc(N * sizeof(int));
    int *next = malloc(M * sizeof(int));
    int *to = malloc(M * sizeof(int));
    int *in_degree = malloc(N * sizeof(int));
    
    memset(head, -1, N * sizeof(int));
    memset(next, 0, M * sizeof(int));
    memset(to, 0, M * sizeof(int));
    memset(in_degree, 0, N * sizeof(int));

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (u >= 0 && u < N && v >= 0 && v < N) {
            to[i] = v;
            next[i] = head[u];
            head[u] = i;
            in_degree[v]++;
        }
    }

    int *result = malloc(N * sizeof(int));
    int count = 0;
    
    // Find all nodes with in_degree 0 and add to result (active pool)
    for (int i = 0; i < N; i++) {
        if (in_degree[i] == 0) {
            result[count++] = i;
        }
    }

    int idx_in_result = 0; // Pointer to next position in result array
    
    while (idx_in_result < count) {
        // Find minimum element in current set [0, count)
        int min_val = -1;
        for (int i = idx_in_result; i < count; i++) {
            if (min_val == -1 || result[i] < min_val) {
                min_val = result[i];
            }
        }

        // Remove min_val from the set by swapping with last element and decrementing count
        int idx = -1;
        for (int i = idx_in_result; i < count; i++) {
            if (result[i] == min_val) {
                idx = i;
                break;
            }
            // If we find it, swap with last element and decrement count
            // But we need to be careful about the loop
        }
        
        // Find and remove min_val
        for (int i = idx_in_result; i < count; i++) {
            if (result[i] == min_val) {
                result[i] = result[count - 1];
                count--;
                break;
            }
        }

        // Process edges from min_val
        int e = head[min_val];
        while (e != -1) {
            int v = to[e];
            in_degree[v]--;
            if (in_degree[v] == 0) {
                result[count++] = v;
            }
            e = next[e];
        }
        
        idx_in_result++;
    }

    // Check if we processed all nodes
    if (count != N) {
        printf("ERROR\n");
    } else {
        for (int i = 0; i < count; i++) {
            printf("%d", result[i]);
            if (i < count - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }

    free(head);
    free(next);
    free(to);
    free(in_degree);
    free(result);
    
    return 0;
}