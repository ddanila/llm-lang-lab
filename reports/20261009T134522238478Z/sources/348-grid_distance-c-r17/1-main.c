#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int H, W, sr, sc, tr, tc;
    if (scanf("%d %d %d %d %d %d", &H, &W, &sr, &sc, &tr, &tc) != 6) return 0;

    char **grid = malloc(H * sizeof(char *));
    for (int i = 0; i < H; i++) {
        grid[i] = malloc(W + 1);
        if (scanf("%s", grid[i]) != 1) break;
    }

    int blocked[20][20];
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            blocked[i][j] = (grid[i][j] == '#');
        }
    }

    if (blocked[sr][sc] || blocked[tr][tc]) {
        printf("-1\n");
        for (int i = 0; i < H; i++) free(grid[i]);
        free(grid);
        return 0;
    }

    int dist[20][20];
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            dist[i][j] = -1;
        }
    }

    int q[400], qx, qy;
    int head = 0, tail = 0;
    q[tail++] = sr * W + sc;
    dist[sr][sc] = 0;

    const int dr[] = {1, -1, 0, 0};
    const int dc[] = {0, 0, 1, -1};

    while (head < tail) {
        int cur = q[head++];
        int r = cur / W;
        int c = cur % W;
        int d = dist[r][c];

        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k];
            int nc = c + dc[k];
            if (nr >= 0 && nr < H && nc >= 0 && nc < W && !blocked[nr][nc] && dist[nr][nc] == -1) {
                dist[nr][nc] = d + 1;
                q[tail++] = nr * W + nc;
            }
        }
    }

    printf("%d\n", dist[tr][tc]);

    for (int i = 0; i < H; i++) free(grid[i]);
    free(grid);
    return 0;
}