#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_H 20
#define MAX_W 20
#define INF 1000000

int main(void) {
    int H, W, sr, sc, tr, tc;
    if (scanf("%d %d %d %d %d %d", &H, &W, &sr, &sc, &tr, &tc) != 6) return 0;

    char grid[MAX_H][MAX_W];
    for (int i = 0; i < H; i++) {
        fgets(grid[i], MAX_W + 1, stdin);
        int len = strlen(grid[i]);
        // Remove newline if present
        while (len > 0 && (grid[i][len-1] == '\n' || grid[i][len-1] == '\r')) {
            grid[i][len-1] = '\0';
            len--;
        }
    }

    // Check endpoints
    if (grid[sr][sc] == '#' || grid[tr][tc] == '#') {
        printf("-1\n");
        return 0;
    }

    // BFS
    int dist[MAX_H][MAX_W];
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            dist[i][j] = INF;
        }
    }

    int q[200]; // Queue for BFS, max cells = 400
    int head = 0, tail = 0;

    dist[sr][sc] = 0;
    q[tail++] = sr * W + sc;

    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    while (head < tail) {
        int curr = q[head++];
        int cx = curr % W;
        int cy = curr / W;

        if (cx == tc && cy == tr) break; // Found target

        for (int k = 0; k < 4; k++) {
            int nx = cx + dx[k];
            int ny = cy + dy[k];

            if (nx >= 0 && nx < H && ny >= 0 && ny < W &&
                grid[nx][ny] != '#' && dist[nx][ny] == INF) {
                dist[nx][ny] = dist[cx][cy] + 1;
                q[tail++] = nx * W + ny;
            }
        }
    }

    printf("%d\n", dist[tr][tc]);
    return 0;
}