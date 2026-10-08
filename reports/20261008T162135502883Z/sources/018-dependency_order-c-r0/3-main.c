#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 25

int adj[MAXN][MAXN];
int in_degree[MAXN];
int order[MAXN];
int zero_in_count;
int processed[MAXN];

int main() {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    memset(adj, 0, sizeof(adj));
    memset(in_degree, 0, sizeof(in_degree));
    memset(processed, 0, sizeof(processed));

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (u >= 0 && u < N && v >= 0 && v < N) {
            adj[u][v]++;
            in_degree[v]++;
        }
    }

    // Initialize zero_in_count with nodes that have no incoming edges
    zero_in_count = 0;
    for (int i = 0; i < N; i++) {
        if (in_degree[i] == 0) {
            order[zero_in_count++] = i;
        }
    }

    int count = 0;
    while (count < zero_in_count) {
        // Find the minimum node among all nodes that are currently available (in_degree == 0 and not processed)
        int min_node = N + 1;
        
        for (int i = 0; i < zero_in_count; i++) {
            if (order[i] >= count && in_degree[order[i]] == 0 && !processed[order[i]]) {
                if (order[i] < min_node) {
                    min_node = order[i];
                }
            }
        }

        if (min_node > N) {
            break; // No more nodes available, cycle detected
        }

        // Process the minimum node
        processed[min_node] = 1;
        count++;

        // Decrease in_degree of neighbors and add new zero-in-degree nodes
        for (int v = 0; v < N; v++) {
            if (adj[min_node][v] > 0) {
                adj[min_node][v]--;
                if (in_degree[v] == 0 && !processed[v]) {
                    order[zero_in_count++] = v;
                }
            }
        }
    }

    if (count < N) {
        printf("ERROR\n");
    } else {
        for (int i = 0; i < N; i++) {
            printf("%d", order[i]);
            if (i < N - 1) printf(" ");
        }
        printf("\n");
    }

    return 0;
}