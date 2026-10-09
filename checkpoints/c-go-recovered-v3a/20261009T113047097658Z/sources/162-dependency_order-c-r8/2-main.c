#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 25
#define MAXM 105

int adj[MAXN][MAXM];
int indeg[MAXN];
int deg_out[MAXN];
int order[MAXN];

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    // Reset adjacency and indegree
    for (int i = 0; i < N; i++) {
        deg_out[i] = 0;
        indeg[i] = 0;
        memset(adj[i], -1, sizeof(int) * MAXM);
    }

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        // Check if edge already exists to avoid duplicates affecting indegree incorrectly
        int found = 0;
        for (int j = 0; j < MAXM - 1; j++) {
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

    // Kahn's algorithm with min-heap simulation using array (since N is small)
    int q_head = 0, q_tail = 0;
    
    // Find all nodes with indegree 0
    for (int i = 0; i < N; i++) {
        if (indeg[i] == 0) {
            order[q_tail++] = i;
        }
    }

    int result_count = 0;
    
    while (q_head < q_tail) {
        // Find minimum node in queue (since we want lexicographically smallest)
        int min_idx = -1, min_val = 1000;
        for (int i = q_head; i < q_tail; i++) {
            if (order[i] < min_val) {
                min_val = order[i];
                min_idx = i;
            }
        }
        
        int u = order[min_idx];
        // Remove from queue
        for (int i = min_idx; i < q_tail - 1; i++) {
            order[i] = order[i + 1];
        }
        q_tail--;
        result_count++;
        order[result_count] = u; // Actually this is wrong, let's fix logic

        // Process neighbors
        for (int j = 0; j < deg_out[u]; j++) {
            int v = adj[u][j];
            indeg[v]--;
            if (indeg[v] == 0) {
                order[q_tail++] = v;
            }
        }
    }

    // Check if all nodes were processed
    if (result_count < N) {
        printf("ERROR\n");
    } else {
        for (int i = 0; i < N; i++) {
            printf("%d%c", order[i], (i == N - 1) ? '\n' : ' ');
        }
    }

    return 0;
}