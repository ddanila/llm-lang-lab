#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int H, W, sr, sc, tr, tc;
    if (scanf("%d %d %d %d %d %d", &H, &W, &sr, &sc, &tr, &tc) != 6) return 0;

    char **grid = malloc(H * sizeof(char *));
    for (int i = 0; i < H; i++) {
        grid[i] = malloc(W + 1);
        scanf("%s", grid[i]);
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

    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};

    for (int d = 0; d < H * W; ) {
        int min_dist = H * W;
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                if (dist[i][j] >= 0 && dist[i][j] + 1 < min_dist) {
                    min_dist = dist[i][j] + 1;
                }
            }
        }
        if (min_dist == H * W) break;

        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                if (dist[i][j] >= 0 && dist[i][j] + 1 < min_dist) {
                    int ni = i + dx[0];
                    int nj = j + dy[0];
                    if (ni >= 0 && ni < H && nj >= 0 && nj < W && grid[ni][nj] == '.' && dist[ni][nj] == -1) {
                        dist[ni][nj] = min_dist;
                    }
                }
            }
        }
    }

    for (int i = 0; i < H; i++) free(grid[i]);
    free(grid);

    printf("%d\n", dist[tr][tc]);
    return 0;
}