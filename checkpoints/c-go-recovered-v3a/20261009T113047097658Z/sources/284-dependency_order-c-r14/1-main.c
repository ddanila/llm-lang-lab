#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    if (N == 0) {
        printf("\n");
        return 0;
    }

    // Adjacency list using linked lists for simplicity
    struct Node {
        int v;
        struct Node *next;
    };

    struct Node **adj = NULL;
    struct Node **in_degree = NULL;

    // Initialize adjacency and in-degree arrays
    adj = (struct Node **)malloc(N * sizeof(struct Node *));
    in_degree = (int *)calloc(N, sizeof(int));

    for (int i = 0; i < N; i++) {
        adj[i] = NULL;
    }

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        
        // Add edge u -> v
        struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
        new_node->v = v;
        new_node->next = adj[u];
        adj[u] = new_node;
        in_degree[v]++;
    }

    // Kahn's algorithm with a min-heap to get lexicographically smallest ordering
    // Since N is small (<=20), we can use a simple array and linear scan for the min element
    
    int result[N];
    int count = 0;
    
    // We'll maintain a list of nodes with in_degree 0
    // For each step, pick the smallest index node with in_degree 0
    
    while (count < N) {
        int min_node = -1;
        for (int i = 0; i < N; i++) {
            if (in_degree[i] == 0 && !adj[i]) { // Wait, we need to track visited nodes differently
                // Actually, let's use a different approach: maintain in_degree and mark processed nodes
            }
        }
    }

    // Let's restart with a cleaner implementation
    int *in_deg = (int *)malloc(N * sizeof(int));
    struct Node **adj_list = (struct Node **)calloc(N, sizeof(struct Node *));
    
    for (int i = 0; i < N; i++) {
        adj_list[i] = NULL;
        in_deg[i] = 0;
    }

    // Reset and re-read edges if needed, but we already read them above
    // Actually, let's rewrite the whole thing cleanly
    
    return 0;
}