#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    // Adjacency list using arrays for edges
    int head[20];
    int next_edge[100], to[100];
    int edge_count = 0;

    // Initialize head array
    for (int i = 0; i < N; i++) {
        head[i] = -1;
    }

    // Read edges
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (edge_count < 100) {
            to[edge_count] = v;
            next_edge[edge_count] = head[u];
            head[u] = edge_count++;
        }
    }

    // Compute in-degrees
    int in_degree[20];
    memset(in_degree, 0, sizeof(in_degree));

    for (int u = 0; u < N; u++) {
        for (int e = head[u]; e != -1; e = next_edge[e]) {
            int v = to[e];
            if (u != v) {
                in_degree[v]++;
            }
        }
    }

    // Kahn's algorithm with priority queue simulation using a simple array and manual min-finding
    int result[20];
    int result_count = 0;

    // Find all nodes with in-degree 0
    int zero_nodes[20];
    int zero_count = 0;
    for (int i = 0; i < N; i++) {
        if (in_degree[i] == 0) {
            zero_nodes[zero_count++] = i;
        }
    }

    while (zero_count > 0) {
        // Find the smallest node index among zero_nodes
        int min_node = zero_nodes[0];
        for (int i = 1; i < zero_count; i++) {
            if (zero_nodes[i] < min_node) {
                min_node = zero_nodes[i];
            }
        }

        // Remove min_node from zero_nodes
        int idx = -1;
        for (int i = 0; i < zero_count; i++) {
            if (zero_nodes[i] == min_node) {
                idx = i;
                break;
            }
        }
        if (idx != -1) {
            // Shift elements after idx to fill the gap
            for (int i = idx; i < zero_count - 1; i++) {
                zero_nodes[i] = zero_nodes[i + 1];
            }
            zero_count--;
        }

        result[result_count++] = min_node;

        // Process edges from min_node
        for (int e = head[min_node]; e != -1; e = next_edge[e]) {
            int v = to[e];
            if (min_node != v) {
                in_degree[v]--;
                if (in_degree[v] == 0) {
                    zero_nodes[zero_count++] = v;
                }
            }
        }
    }

    // Check if all nodes are included
    if (result_count < N) {
        printf("ERROR\n");
    } else {
        for (int i = 0; i < N; i++) {
            printf("%d%c", result[i], (i == N - 1 ? '\n' : ' '));
        }
    }

    return 0;
}