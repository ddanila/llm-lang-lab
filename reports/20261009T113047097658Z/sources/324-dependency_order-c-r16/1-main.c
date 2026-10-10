#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 20

int adj[MAXN][MAXN];
int indegree[MAXN];
int order[MAXN];
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

    int head = 0;
    int count = 0;

    for (int i = 0; i < n; i++) {
        if (indegree[i] == 0) {
            order[head++] = i;
        }
    }

    while (head < n) {
        int min_node = -1;
        int min_indegree = MAXN;

        for (int i = 0; i < n; i++) {
            if (indegree[i] == 0) {
                if (min_indegree > indegree[i]) {
                    min_indegree = indegree[i];
                    min_node = i;
                } else if (min_indegree == indegree[i] && min_node != -1 && min_node > i) {
                    min_node = i;
                }
            }
        }

        if (min_node == -1) break;

        order[head++] = min_node;
        indegree[min_node]++; // Temporarily mark as processed by increasing its own indegree? No.
        
        // Actually, we need to simulate removal. Let's use a visited array or decrement neighbors.
        // Better approach: Use a separate "available" flag or just decrement neighbors' indegrees.
    }

    // Re-do with correct logic using a list of available nodes
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

        order[idx++] = min_val;

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

        // Decrement indegree of neighbors
        for (int v = 0; v < n; v++) {
            if (adj[min_val][v]) {
                indegree[v]--;
                if (indegree[v] == 0) {
                    avail[avail_count++] = v;
                }
            }
        }
    }

    if (idx < n) {
        printf("ERROR\n");
    } else {
        for (int i = 0; i < n; i++) {
            printf("%d%c", order[i], (i == n - 1) ? '\n' : ' ');
        }
    }

    return 0;
}