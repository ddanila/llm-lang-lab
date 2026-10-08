#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    // Adjacency list: adj[u] contains v for edge u -> v
    int *adj = malloc(N * sizeof(int));
    memset(adj, 0, N * sizeof(int));
    int deg[N];
    memset(deg, 0, N * sizeof(deg));

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u] = adj[u] == -1 ? v : (adj[u] == v ? adj[u] : adj[u]);
        // Simple approach: store edges in a list per node
        // But we need dynamic adjacency. Let's use a different structure.
    }

    // Re-implement with proper adjacency list using linked lists or arrays
    free(adj);

    int head[N];
    memset(head, -1, N * sizeof(int));
    int count = 0;

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        // Add edge u -> v
        int new_node = count++;
        deg[v]++;
        head[u] = new_node;
        // We need to store the next node pointer. Let's use a separate array for next pointers.
    }

    // Actually, let's use a simpler approach: since N <= 20, we can use an adjacency matrix or simple arrays.
    // But M can be up to 100, so we need to handle multiple edges.
    // Let's use a linked list for each node.

    int *next = malloc(count * sizeof(int));
    memset(next, -1, count * sizeof(int));
    int *to = malloc(count * sizeof(int));

    head[N] = {0};
    memset(head, -1, N * sizeof(int));
    memset(deg, 0, N * sizeof(int));

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        int new_node = count++;
        to[new_node] = v;
        next[new_node] = head[u];
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
        int min_indeg = N + 1;

        for (int i = 0; i < N; i++) {
            if (indegree[i] == 0 && i >= 0) {
                if (min_node == -1 || i < min_node) {
                    min_node = i;
                    min_indeg = indegree[i];
                }
            }
        }

        if (min_node == -1) {
            // Cycle detected
            printf("ERROR\n");
            free(head);
            free(next);
            free(to);
            return 0;
        }

        result[count_result++] = min_node;
        indegree[min_node]--;

        for (int e = head[min_node]; e != -1; e = next[e]) {
            int v = to[e];
            indegree[v]--;
        }
    }

    for (int i = 0; i < N; i++) {
        printf("%d%c", result[i], i == N - 1 ? '\n' : ' ');
    }

    free(head);
    free(next);
    free(to);
    return 0;
}