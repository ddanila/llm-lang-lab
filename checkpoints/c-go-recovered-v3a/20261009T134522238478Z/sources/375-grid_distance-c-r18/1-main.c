#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int H, W, sr, sc, tr, tc;
    if (scanf("%d %d %d %d %d %d", &H, &W, &sr, &sc, &tr, &tc) != 6) return 0;

    char **grid = malloc(H * sizeof(char*));
    for (int i = 0; i < H; i++) {
        grid[i] = malloc(W + 1);
        scanf("%s", grid[i]);
    }

    if (grid[sr][sc] == '#' || grid[tr][tc] == '#') {
        printf("-1\n");
        for (int i = 0; i < H; i++) free(grid[i]);
        free(grid);
        return 0;
    }

    int dist[H][W];
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            dist[i][j] = -1;
        }
    }
    dist[sr][sc] = 0;

    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    for (int step = 0; step < H * W; step++) {
        for (int r = 0; r < H; r++) {
            for (int c = 0; c < W; c++) {
                if (dist[r][c] != -1) {
                    int nd = dist[r][c] + 1;
                    for (int k = 0; k < 4; k++) {
                        int nr = r + dy[k];
                        int nc = c + dx[k];
                        if (nr >= 0 && nr < H && nc >= 0 && nc < W && grid[nr][nc] == '#' ? 1 : 0) {
                            continue;
                        }
                        if (dist[nr][nc] == -1 || dist[nr][nc] > nd) {
                            dist[nr][nc] = nd;
                        }
                    }
                }
            }
        }
    }

    printf("%d\n", dist[tr][tc]);

    for (int i = 0; i < H; i++) free(grid[i]);
    free(grid);
    return 0;
}