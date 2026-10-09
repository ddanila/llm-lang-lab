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
    // We use a min-heap approach by repeatedly scanning for the smallest available node
    
    int in_degree[100];
    for (int i = 0; i < N; i++) {
        in_degree[i] = 0;
    }

    for (int u = 0; u < N; u++) {
        for (int e = head[u]; e != -1; e = next[e]) {
            int v = to[e];
            in_degree[v]++;
        }
    }

    int result[100];
    int count = 0;
    
    // Use a simple array and scan for min available node each time
    while (count < N) {
        int min_node = -1;
        for (int i = 0; i < N; i++) {
            if (in_degree[i] == 0 && result[i] == -1) { // Not yet in result
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

        result[count++] = min_node;
        in_degree[min_node] = -1; // Mark as used
        
        // Decrease in-degree of neighbors
        for (int e = head[min_node]; e != -1; e = next[e]) {
            int v = to[e];
            in_degree[v]--;
        }
    }

    for (int i = 0; i < N; i++) {
        printf("%d%c", result[i], (i == N-1) ? '\n' : ' ');
    }

    return 0;
}