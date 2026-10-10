#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Edge {
    int to;
    struct Edge *next;
} Edge;

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    Edge **head = malloc(N * sizeof(Edge*));
    memset(head, 0, N * sizeof(Edge*));
    int deg[N];
    memset(deg, 0, N * sizeof(deg));

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        Edge *e = malloc(sizeof(Edge));
        e->to = v;
        e->next = head[u];
        head[u] = e;
        deg[v]++;
    }

    // Kahn's algorithm with priority queue for lexicographically smallest order
    // Since N is small (<=20), we can use a simple array and scan for minimum degree 0 node.
    
    int indegree[N];
    memcpy(indegree, deg, N * sizeof(int));

    int result[N];
    int count_result = 0;

    while (count_result < N) {
        int min_node = -1;

        for (int i = 0; i < N; i++) {
            if (indegree[i] == 0) {
                if (min_node == -1 || i < min_node) {
                    min_node = i;
                }
            }
        }

        if (min_node == -1) {
            // Cycle detected
            printf("ERROR\n");
            for (int i = 0; i < N; i++) {
                Edge *e = head[i];
                while (e != NULL) {
                    Edge *next_e = e->next;
                    free(e);
                    e = next_e;
                }
            }
            free(head);
            return 0;
        }

        result[count_result++] = min_node;
        indegree[min_node]--;

        for (Edge *e = head[min_node]; e != NULL; e = e->next) {
            indegree[e->to]--;
        }
    }

    for (int i = 0; i < N; i++) {
        printf("%d%c", result[i], i == N - 1 ? '\n' : ' ');
    }

    for (int i = 0; i < N; i++) {
        Edge *e = head[i];
        while (e != NULL) {
            Edge *next_e = e->next;
            free(e);
            e = next_e;
        }
    }
    free(head);
    return 0;
}