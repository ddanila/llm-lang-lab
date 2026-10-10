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

    // Adjacency list using linked lists
    struct Node {
        int v;
        struct Node *next;
    };
    
    struct Node **adj = calloc(N, sizeof(struct Node*));
    int *indeg = calloc(N, sizeof(int));

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        
        // Create new node
        struct Node *new_node = malloc(sizeof(struct Node));
        new_node->v = v;
        new_node->next = adj[u];
        adj[u] = new_node;
        indeg[v]++;
    }

    int *order = calloc(N, sizeof(int));
    int order_count = 0;

    // Min-heap simulation: use array and scan for minimum
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
        // Find minimum node in queue
        int u = q[q_head];
        for (int i = q_head + 1; i < q_tail; i++) {
            if (q[i] < u) {
                u = q[i];
            }
        }
        
        // Remove u from queue
        for (int i = q_head; i < q_tail - 1; i++) {
            q[i] = q[i + 1];
        }
        q_tail--;
        
        order[order_count++] = u;

        // Process all neighbors of u
        struct Node *p = adj[u];
        while (p != NULL) {
            int v = p->v;
            indeg[v]--;
            if (indeg[v] == 0) {
                q[q_tail++] = v;
            }
            p = p->next;
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