#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    // Adjacency list: head[u] -> next[v], store edge index
    // We need to track in-degrees and build the graph.
    // Since N <= 20, we can use a simple adjacency matrix or list.
    // Let's use adjacency lists with arrays for edges.

    int *adj = malloc(N * sizeof(int));
    int *next = malloc(M * sizeof(int));
    int *to = malloc(M * sizeof(int));
    int *indeg = calloc(N, sizeof(int));

    int head[20];
    for (int i = 0; i < N; i++) head[i] = -1;

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        // Edge from u to v
        next[i] = head[u];
        to[i] = v;
        head[u] = i;
        if (i == 0 || u != v) { // self-loops are allowed but don't affect topological order if we ignore them? 
            // Actually, a self-loop u->u creates a cycle. So we must detect cycles.
            // But the problem says "Duplicate edges and self-edges are allowed".
            // A self-edge u->u is a cycle. So if u==v, it's a cycle.
        }
        if (u == v) {
            // Self-loop -> cycle
            printf("ERROR\n");
            free(adj); free(next); free(to); free(indeg);
            return 0;
        }
        indeg[v]++;
    }

    // Kahn's algorithm with a min-heap (priority queue) to get lexicographically smallest order.
    // Since N is small (<=20), we can use a simple array and scan for the minimum node with indegree 0.
    
    int result[20];
    int count = 0;

    while (count < N) {
        int min_node = -1;
        // Find the smallest node index with indegree 0
        for (int i = 0; i < N; i++) {
            if (indeg[i] == 0) {
                if (min_node == -1 || i < min_node) {
                    min_node = i;
                }
            }
        }

        if (min_node == -1) {
            // No node with indegree 0 -> cycle exists
            printf("ERROR\n");
            free(adj); free(next); free(to); free(indeg);
            return 0;
        }

        result[count++] = min_node;

        // Decrease indegree of neighbors
        for (int e = head[min_node]; e != -1; e = next[e]) {
            int v = to[e];
            indeg[v]--;
        }
    }

    for (int i = 0; i < N; i++) {
        printf("%d%c", result[i], (i == N - 1) ? '\n' : ' ');
    }

    free(adj); free(next); free(to); free(indeg);
    return 0;
}