#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 25

int adj[MAXN][MAXN];
int in_degree[MAXN];
int order[MAXN];
int count;

int main() {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    memset(adj, 0, sizeof(adj));
    memset(in_degree, 0, sizeof(in_degree));

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (u >= 0 && u < N && v >= 0 && v < N) {
            adj[u][v]++;
            in_degree[v]++;
        }
    }

    int zero_in_count = 0;
    for (int i = 0; i < N; i++) {
        if (in_degree[i] == 0) {
            order[zero_in_count++] = i;
        }
    }

    count = 0;
    while (count < zero_in_count) {
        int min_idx = -1;
        int min_val = N + 1;
        for (int i = 0; i < zero_in_count; i++) {
            if (in_degree[order[i]] == 0 && order[i] < min_val) {
                min_val = order[i];
                min_idx = i;
            }
        }

        if (min_idx != -1) {
            int node = order[min_idx];
            for (int i = 0; i < zero_in_count; i++) {
                if (order[i] == node) {
                    in_degree[order[i]] = N + 1;
                    break;
                }
            }

            count++;
            int added = 0;
            for (int v = 0; v < N; v++) {
                if (adj[node][v] > 0) {
                    adj[node][v]--;
                    if (in_degree[v] == 0) {
                        in_degree[v] = -1; // mark as added to zero_in list temporarily
                        order[zero_in_count++] = v;
                    }
                }
            }
        } else {
            break;
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