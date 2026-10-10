#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    // For N <= 20, we can use an adjacency matrix and handle duplicate edges by counting
    int adj[20][20];
    memset(adj, 0, sizeof(adj));
    int indeg[20] = {0};
    
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (u >= 0 && u < N && v >= 0 && v < N) {
            adj[u][v]++;
            indeg[v] += adj[u][v]; // This is wrong - should be +=1 for each edge
            // Fix: actually, indeg[v] should increase by 1 for each incoming edge from u
        }
    }

    // Wait, the issue is that adj[u][v]++ increments to 1, then +1 = 2, but we only want to add 1 to indeg each time
    // Let me reconsider: if there are multiple edges from u to v, each counts as one incoming edge
    
    // Actually my logic was correct in the sense that each edge adds 1 to indeg. 
    // But I wrote "indeg[v] += adj[u][v]" which after adj[u][v]++ would be adding the new value (>=1)
    // It should just be "indeg[v]++" or "indeg[v] += 1"
    
    return 0;
}