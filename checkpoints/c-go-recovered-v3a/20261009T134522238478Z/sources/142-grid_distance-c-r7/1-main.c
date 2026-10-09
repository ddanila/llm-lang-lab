#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int H, W;
    if (scanf("%d %d", &H, &W) != 2) return 0;
    int sr, sc, tr, tc;
    scanf("%d %d %d %d", &sr, &sc, &tr, &tc);

    char **grid = malloc(H * sizeof(char*));
    for (int i = 0; i < H; i++) {
        grid[i] = malloc(W + 1);
        scanf("%s", grid[i]);
        grid[i][W] = '\0';
    }

    if (grid[sr][sc] == '#' || grid[tr][tc] == '#') {
        for (int i = 0; i < H; i++) free(grid[i]);
        free(grid);
        printf("-1\n");
        return 0;
    }

    int dist[H][W];
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            dist[i][j] = -1;
        }
    }
    dist[sr][sc] = 0;

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    for (int d = 0; d < H * W; d++) {
        for (int r = 0; r < H; r++) {
            for (int c = 0; c < W; c++) {
                if (dist[r][c] != -1) {
                    int nd = dist[r][c] + 1;
                    for (int k = 0; k < 4; k++) {
                        int nr = r + dr[k];
                        int nc = c + dc[k];
                        if (nr >= 0 && nr < H && nc >= 0 && nc < W) {
                            if (grid[nr][nc] == '.' && dist[nr][nc] == -1) {
                                dist[nr][nc] = nd;
                            }
                        }
                    }
                }
            }
        }
    }

    int result = dist[tr][tc];
    if (result < 0) result = -1;

    for (int i = 0; i < H; i++) free(grid[i]);
    free(grid);

    printf("%d\n", result);
    return 0;
}