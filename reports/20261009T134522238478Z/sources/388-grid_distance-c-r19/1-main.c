#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int H, W, sr, sc, tr, tc;
    if (scanf("%d %d %d %d %d %d", &H, &W, &sr, &sc, &tr, &tc) != 6) return 0;

    char **grid = malloc(H * sizeof(char *));
    for (int i = 0; i < H; i++) {
        grid[i] = malloc(W + 1);
        if (!grid[i]) return 0;
    }

    for (int i = 0; i < H; i++) {
        int n = 0;
        while (n < W) {
            char c = getchar();
            if (c == '\n' || c == EOF) break;
            grid[i][n++] = c;
        }
        grid[i][n] = '\0';
    }

    // Check endpoints
    if (grid[sr][sc] == '#' || grid[tr][tc] == '#') {
        printf("-1\n");
        for (int i = 0; i < H; i++) free(grid[i]);
        free(grid);
        return 0;
    }

    // BFS
    int dist[H][W];
    memset(dist, -1, sizeof(dist));

    int q[200]; // queue for max 400 cells
    int head = 0, tail = 0;

    dist[sr][sc] = 0;
    q[tail++] = sr * W + sc;

    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};

    while (head < tail) {
        int cur = q[head++];
        int cx = cur % W;
        int cy = cur / W;
        int d = dist[cy][cx];

        if (cx == tc && cy == tr) break;

        for (int k = 0; k < 4; k++) {
            int nx = cx + dx[k];
            int ny = cy + dy[k];
            if (nx >= 0 && nx < W && ny >= 0 && ny < H && grid[ny][nx] != '#' && dist[ny][nx] == -1) {
                dist[ny][nx] = d + 1;
                q[tail++] = ny * W + nx;
            }
        }
    }

    printf("%d\n", dist[tr][tc]);

    for (int i = 0; i < H; i++) free(grid[i]);
    free(grid);

    return 0;
}