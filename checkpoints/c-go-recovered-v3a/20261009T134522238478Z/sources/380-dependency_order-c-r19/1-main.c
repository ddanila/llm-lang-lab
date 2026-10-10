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

    int *adj = calloc(N, sizeof(int));
    int *indeg = calloc(N, sizeof(int));
    adj[N] = 0;
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u] |= (1 << v);
        if (!((adj[u] >> v) & 1)) {
            indeg[v]++;
        }
    }

    // To get lexicographically smallest order, we use a min-heap for nodes with indegree 0.
    // Since N <= 20, we can just scan for the minimum each time.
    
    int *order = calloc(N, sizeof(int));
    int order_count = 0;

    int *q = calloc(N, sizeof(int));
    int q_head = 0;
    int q_tail = 0;

    // Initialize queue with all nodes having indegree 0
    for (int i = 0; i < N; i++) {
        if (indeg[i] == 0) {
            q[q_tail++] = i;
        }
    }

    while (q_head < q_tail) {
        int u = q[q_head++];
        order[order_count++] = u;

        // Iterate through all nodes v such that there is an edge u -> v
        for (int v = 0; v < N; v++) {
            if ((adj[u] >> v) & 1) {
                indeg[v]--;
                if (indeg[v] == 0) {
                    q[q_tail++] = v;
                }
            }
        }
    }

    if (order_count != N) {
        printf("ERROR\n");
    } else {
        for (int i = 0; i < N; i++) {
            if (i > 0) printf(" ");
            printf("%d", order[i]);
        }
        printf("\n");
    }

    free(adj);
    free(indeg);
    free(order);
    free(q);

    return 0;
}