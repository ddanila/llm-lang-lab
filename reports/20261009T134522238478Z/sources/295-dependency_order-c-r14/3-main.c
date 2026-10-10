#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    // Adjacency list: head[u] points to first edge from u
    static int head[100];
    static int next_edge[10000]; 
    static int target[10000];    
    static int indegree[100];

    for (int i = 0; i < N; i++) {
        head[i] = -1;
        indegree[i] = 0;
    }

    int edge_count = 0;

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (u < 0 || u >= N || v < 0 || v >= N) continue;
        
        // Add edge u->v
        next_edge[edge_count] = head[u];
        target[edge_count] = v;
        head[u] = edge_count;
        indegree[v]++;
        edge_count++;
    }

    static int result[100];
    int idx = 0;

    // Kahn's algorithm with priority queue (simulated by scanning for min)
    while (idx < N) {
        int min_node = -1;
        // Find smallest node with indegree 0
        for (int j = 0; j < N; j++) {
            if (indegree[j] == 0) {
                if (min_node == -1 || j < min_node) {
                    min_node = j;
                }
            }
        }
        
        if (min_node == -1) {
            // Cycle detected
            printf("ERROR\n");
            return 0;
        }
        
        result[idx++] = min_node;
        
        // Decrease indegree of all neighbors
        for (int e = head[min_node]; e != -1; e = next_edge[e]) {
            int v = target[e];
            indegree[v]--;
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