#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    // Adjacency list: head[u] -> next[v], value is v
    static int adj[100];
    for (int i = 0; i < N; i++) {
        adj[i] = -1;
    }

    // Edge count for each node to build indegree later
    static int indegree[100] = {0};

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (u < 0 || u >= N || v < 0 || v >= N) continue; // safety
        // Insert edge u->v at the front of adj[u] to allow easy insertion
        int next = adj[u];
        adj[u] = v;
        indegree[v]++;
    }

    // Kahn's algorithm with priority queue (simulated by scanning for min)
    // We need lexicographically smallest topological order.
    // At each step, pick the smallest node with indegree 0.
    
    static int result[100];
    int idx = 0;

    // We'll use an array to track current indegrees and modify them
    for (int i = 0; i < N; i++) {
        if (indegree[i] == 0) {
            // Find min node with indegree 0
            int min_node = -1;
            for (int j = 0; j < N; j++) {
                if (indegree[j] == 0) {
                    if (min_node == -1 || j < min_node) {
                        min_node = j;
                    }
                }
            }
            if (min_node != -1) {
                result[idx++] = min_node;
                // Decrease indegree of all neighbors
                for (int e = adj[min_node]; e != -1; e = adj[e]) {
                    indegree[e]--;
                }
            } else {
                // Cycle detected
                printf("ERROR\n");
                return 0;
            }
        }
    }

    if (idx != N) {
        printf("ERROR\n");
    } else {
        for (int i = 0; i < N; i++) {
            if (i > 0) printf(" ");
            printf("%d", result[i]);
        }
        printf("\n");
    }

    return 0;
}