#include <stdio.h>
#include <stdlib.h>

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

    struct Node **adj = NULL;
    int *in_degree = NULL;

    adj = (struct Node **)malloc(N * sizeof(struct Node *));
    in_degree = (int *)calloc(N, sizeof(int));

    for (int i = 0; i < N; i++) {
        adj[i] = NULL;
    }

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        
        struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
        new_node->v = v;
        new_node->next = adj[u];
        adj[u] = new_node;
        in_degree[v]++;
    }

    int result[N];
    int count = 0;
    
    while (count < N) {
        int min_node = -1;
        for (int i = 0; i < N; i++) {
            if (in_degree[i] == 0) {
                min_node = i;
                break;
            }
        }
        
        if (min_node == -1) {
            printf("ERROR\n");
            return 0;
        }
        
        result[count++] = min_node;
        in_degree[min_node] = -1; // Mark as processed
        
        struct Node *curr = adj[min_node];
        while (curr != NULL) {
            if (in_degree[curr->v] > 0) {
                in_degree[curr->v]--;
            }
            curr = curr->next;
        }
    }
    
    for (int i = 0; i < N; i++) {
        printf("%d", result[i]);
        if (i < N - 1) printf(" ");
    }
    printf("\n");

    return 0;
}