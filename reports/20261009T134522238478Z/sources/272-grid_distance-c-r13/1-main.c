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

    if (sr < 0 || sr >= H || sc < 0 || sc >= W || tr < 0 || tr >= H || tc < 0 || tc >= W) {
        for (int i = 0; i < H; i++) free(grid[i]);
        free(grid);
        printf("-1\n");
        return 0;
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

    int q[H * W], head = 0, tail = 0;
    q[tail++] = sr * W + sc;

    while (head < tail) {
        int cur = q[head++];
        int r = cur / W;
        int c = cur % W;

        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k];
            int nc = c + dc[k];

            if (nr >= 0 && nr < H && nc >= 0 && nc < W && dist[nr][nc] == -1 && grid[nr][nc] == '.') {
                dist[nr][nc] = dist[r][c] + 1;
                q[tail++] = nr * W + nc;
            }
        }
    }

    printf("%d\n", dist[tr][tc]);

    for (int i = 0; i < H; i++) free(grid[i]);
    free(grid);

    return 0;
}