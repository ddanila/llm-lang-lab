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

    // Adjacency list: adj[u] contains list of v such that u -> v
    int *adj = malloc(N * sizeof(int));
    memset(adj, 0, N * sizeof(int));
    int degrees[N];
    memset(degrees, 0, sizeof(degrees));
    
    // Track number of edges from each node to manage adjacency list size
    for (int i = 0; i < N; i++) {
        adj[i] = 0;
    }

    int edge_count[N];
    memset(edge_count, 0, sizeof(edge_count));

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (u >= 0 && u < N && v >= 0 && v < N) {
            // Add edge u -> v
            adj[u] = adj[u] + edge_count[u]; // Shift? No, we need linked list style or array
            // Let's use simple adjacency list with next pointers
        }
    }

    // Actually, let's rebuild with a proper adjacency list
    free(adj);
    int *head = malloc(N * sizeof(int));
    memset(head, -1, N * sizeof(int));
    int *next = malloc(M * sizeof(int));
    memset(next, 0, M * sizeof(int));
    int *to = malloc(M * sizeof(int));
    memset(to, 0, M * sizeof(int));

    for (int i = 0; i < N; i++) {
        head[i] = -1;
    }

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (u >= 0 && u < N && v >= 0 && v < N) {
            to[i] = v;
            next[i] = head[u];
            head[u] = i;
            degrees[v]++;
        }
    }

    // Kahn's algorithm with a priority queue (min-heap) for lexicographically smallest order
    // Since N <= 20, we can use a simple array and scan for min each time
    int in_degree[N];
    memset(in_degree, 0, sizeof(in_degree));
    
    // Recompute degrees properly
    memset(head, -1, N * sizeof(int));
    memset(next, 0, M * sizeof(int));
    memset(to, 0, M * sizeof(int));
    memset(in_degree, 0, sizeof(in_degree));

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

    // Read remaining inputs for M edges (we already read them above, but we need to handle the loop correctly)
    // Actually, the above loops consumed M lines. Let's restart properly.
    
    free(head);
    free(next);
    free(to);
    head = malloc(N * sizeof(int));
    next = malloc(M * sizeof(int));
    to = malloc(M * sizeof(int));
    in_degree = malloc(N * sizeof(int));
    memset(head, -1, N * sizeof(int));
    memset(next, 0, M * sizeof(int));
    memset(to, 0, M * sizeof(int));
    memset(in_degree, 0, sizeof(int));

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

    // Kahn's algorithm with min-heap simulation (since N is small)
    int result[N];
    int count = 0;
    
    // Find all nodes with in_degree 0
    for (int i = 0; i < N; i++) {
        if (in_degree[i] == 0) {
            result[count++] = i;
        }
    }

    while (count > 0) {
        // Find minimum element in current set
        int min_val = -1;
        for (int i = 0; i < count; i++) {
            if (min_val == -1 || result[i] < min_val) {
                min_val = result[i];
            }
        }

        // Remove min_val from the set
        int idx = -1;
        for (int i = 0; i < count; i++) {
            if (result[i] == min_val) {
                idx = i;
                break;
            }
        }
        result[idx] = result[count - 1];
        count--;

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
    }

    // Check if we processed all nodes
    if (count != N) {
        printf("ERROR\n");
    } else {
        for (int i = 0; i < N; i++) {
            printf("%d", result[i]);
            if (i < N - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }

    free(head);
    free(next);
    free(to);
    free(in_degree);
    
    return 0;
}