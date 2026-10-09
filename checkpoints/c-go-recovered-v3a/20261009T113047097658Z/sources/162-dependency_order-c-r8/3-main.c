#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 25
#define MAXM 105

int adj[MAXN][MAXM];
int indeg[MAXN];
int deg_out[MAXN];

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    // Reset adjacency and indegree
    for (int i = 0; i < N; i++) {
        deg_out[i] = 0;
        indeg[i] = 0;
    }

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        // Add edge if not already present
        int found = 0;
        for (int j = 0; j < deg_out[u]; j++) {
            if (adj[u][j] == v) {
                found = 1;
                break;
            }
        }
        if (!found && deg_out[u] < MAXM - 1) {
            adj[u][deg_out[u]] = v;
            deg_out[u]++;
            indeg[v]++;
        }
    }

    // Kahn's algorithm: maintain nodes with indegree 0 in sorted order
    int result[MAXN];
    int result_count = 0;

    // Find all nodes with indegree 0 and sort them
    int zero_nodes[MAXN];
    int zero_count = 0;
    for (int i = 0; i < N; i++) {
        if (indeg[i] == 0) {
            zero_nodes[zero_count++] = i;
        }
    }

    // Sort zero nodes (already sorted since we iterate in order)
    // Now process
    while (result_count < N) {
        int u = zero_nodes[result_count];
        result[result_count] = u;
        result_count++;
        
        // Remove u from zero_nodes and add newly freed nodes
        for (int i = 0; i < zero_count - 1; i++) {
            zero_nodes[i] = zero_nodes[i + 1];
        }
        zero_count--;
        
        // Process neighbors
        for (int j = 0; j < deg_out[u]; j++) {
            int v = adj[u][j];
            indeg[v]--;
            if (indeg[v] == 0) {
                // Insert v into sorted position in zero_nodes
                int pos = zero_count;
                while (pos > 0 && zero_nodes[pos - 1] > v) {
                    zero_nodes[pos] = zero_nodes[pos - 1];
                    pos--;
                }
                zero_nodes[pos] = v;
                zero_count++;
            }
        }
    }

    // Check if all nodes were processed (cycle detection)
    if (result_count < N) {
        printf("ERROR\n");
    } else {
        for (int i = 0; i < N; i++) {
            printf("%d%c", result[i], (i == N - 1) ? '\n' : ' ');
        }
    }

    return 0;
}