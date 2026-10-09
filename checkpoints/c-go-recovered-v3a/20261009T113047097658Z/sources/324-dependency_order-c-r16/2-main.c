#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 20

int adj[MAXN][MAXN];
int indegree[MAXN];
int n, m;

int main() {
    int u, v;
    if (scanf("%d %d", &n, &m) != 2) return 0;

    memset(adj, 0, sizeof(adj));
    memset(indegree, 0, sizeof(indegree));

    for (int i = 0; i < m; i++) {
        scanf("%d %d", &u, &v);
        if (adj[u][v] == 0) {
            adj[u][v] = 1;
            indegree[v]++;
        }
    }

    // Kahn's algorithm with priority: always pick smallest available node
    int avail[MAXN];
    int avail_count = 0;
    for (int i = 0; i < n; i++) {
        if (indegree[i] == 0) {
            avail[avail_count++] = i;
        }
    }

    int idx = 0;
    while (idx < n && avail_count > 0) {
        // Find smallest node in avail list
        int min_val = avail[0];
        for (int i = 1; i < avail_count; i++) {
            if (avail[i] < min_val) {
                min_val = avail[i];
            }
        }

        // Remove min_val from avail list and decrement neighbors
        int found = -1;
        for (int i = 0; i < avail_count; i++) {
            if (avail[i] == min_val) {
                found = i;
                break;
            }
        }

        // Shift elements after found to left
        for (int i = found + 1; i < avail_count; i++) {
            avail[i - 1] = avail[i];
        }
        avail_count--;

        printf("%d", min_val);
        if (idx < n - 1) printf(" ");

        // Decrement indegree of neighbors
        for (int v = 0; v < n; v++) {
            if (adj[min_val][v]) {
                indegree[v]--;
                if (indegree[v] == 0) {
                    avail[avail_count++] = v;
                }
            }
        }
        idx++;
    }

    printf("\n");

    // Check for cycle
    if (idx < n) {
        printf("ERROR\n");
        return 0;
    }

    return 0;
}