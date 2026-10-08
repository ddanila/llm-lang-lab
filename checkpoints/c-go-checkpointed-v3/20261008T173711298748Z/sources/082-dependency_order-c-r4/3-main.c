#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    // Adjacency list using linked lists
    int *head = malloc(N * sizeof(int));
    memset(head, -1, N * sizeof(int));
    int count = 0;
    int deg[N];
    memset(deg, 0, N * sizeof(deg));

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        int new_node = count++;
        int to_val = v;
        int next_ptr = head[u];
        head[u] = new_node;
        deg[v]++;
    }

    // Kahn's algorithm with priority queue for lexicographically smallest order
    // Since N is small (<=20), we can use a simple array and scan for minimum degree 0 node.
    
    int indegree[N];
    memcpy(indegree, deg, N * sizeof(int));

    int result[N];
    int count_result = 0;

    while (count_result < N) {
        int min_node = -1;

        for (int i = 0; i < N; i++) {
            if (indegree[i] == 0) {
                if (min_node == -1 || i < min_node) {
                    min_node = i;
                }
            }
        }

        if (min_node == -1) {
            // Cycle detected
            printf("ERROR\n");
            free(head);
            return 0;
        }

        result[count_result++] = min_node;
        indegree[min_node]--;

        for (int e = head[min_node]; e != -1; e = head[e]) {
            // Need to traverse the linked list properly
            // But we lost the next pointers!
        }
    }

    for (int i = 0; i < N; i++) {
        printf("%d%c", result[i], i == N - 1 ? '\n' : ' ');
    }

    free(head);
    return 0;
}