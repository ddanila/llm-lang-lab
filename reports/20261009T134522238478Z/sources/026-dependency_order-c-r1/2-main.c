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
    int head[100];
    int next[10000];
    int to[10000];
    int edge_count = 0;

    for (int i = 0; i < N; i++) {
        head[i] = -1;
    }

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (u >= N || v >= N) continue; // Should not happen per spec
        
        next[edge_count] = head[u];
        to[edge_count] = v;
        head[u] = edge_count++;
    }

    // Kahn's algorithm with lexicographically smallest ordering
    int in_degree[100];
    for (int i = 0; i < N; i++) {
        in_degree[i] = 0;
    }

    for (int u = 0; u < N; u++) {
        for (int e = head[u]; e != -1; e = next[e]) {
            int v = to[e];
            if (v >= 0 && v < N) {
                in_degree[v]++;
            }
        }
    }

    // Use a simple array and scan for min available node each time
    while (edge_count > 0) {
        int min_node = -1;
        for (int i = 0; i < N; i++) {
            if (in_degree[i] == 0 && head[i] != -1) { // Has outgoing edges but in_degree is 0
                if (min_node == -1 || i < min_node) {
                    min_node = i;
                }
            } else if (in_degree[i] == 0 && head[i] == -1) { // No outgoing edges, also valid
                if (min_node == -1 || i < min_node) {
                    min_node = i;
                }
            }
        }

        if (min_node == -1) {
            // No node with in_degree 0 found -> cycle
            printf("ERROR\n");
            return 0;
        }

        head[min_node] = -1; // Mark as used by setting head to -1
        
        // Decrease in-degree of neighbors
        for (int e = head[min_node]; e != -1 && head[min_node] != -1; e = next[e]) {
            int v = to[e];
            if (v >= 0 && v < N) {
                in_degree[v]--;
            }
        }
    }

    // Re-scan to find all nodes with in_degree 0
    int count = 0;
    for (int i = 0; i < N; i++) {
        if (in_degree[i] == 0) {
            printf("%d%c", i, (count++ == N-1) ? '\n' : ' ');
        }
    }

    return 0;
}