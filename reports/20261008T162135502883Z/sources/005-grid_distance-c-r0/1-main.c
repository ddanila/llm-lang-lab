#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int H, W, sr, sc, tr, tc;
    if (scanf("%d %d %d %d %d %d", &H, &W, &sr, &sc, &tr, &tc) != 6) {
        return 0;
    }

    char **grid = malloc(H * sizeof(char *));
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

    if (sr == tr && sc == tc) {
        printf("0\n");
        for (int i = 0; i < H; i++) free(grid[i]);
        free(grid);
        return 0;
    }

    int q[H * W];
    int head = 0, tail = 0;
    dist[sr][sc] = 0;
    q[tail++] = sr * W + sc;

    int dr[] = {1, -1, 0, 0};
    int dc[] = {0, 0, 1, -1};

    while (head < tail) {
        int curr = q[head++];
        int r = curr / W;
        int c = curr % W;
        int d = dist[r][c];

        if (d > 0 && r == tr && c == tc) {
            printf("%d\n", d);
            for (int i = 0; i < H; i++) free(grid[i]);
            free(grid);
            return 0;
        }

        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k];
            int nc = c + dc[k];

            if (nr >= 0 && nr < H && nc >= 0 && nc < W && grid[nr][nc] != '#' && dist[nr][nc] == -1) {
                dist[nr][nc] = d + 1;
                q[tail++] = nr * W + nc;
            }
        }
    }

    printf("-1\n");
    for (int i = 0; i < H; i++) free(grid[i]);
    free(grid);
    return 0;
}