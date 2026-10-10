#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int H, W, sr, sc, tr, tc;
    if (scanf("%d %d %d %d %d %d", &H, &W, &sr, &sc, &tr, &tc) != 6) {
        return 0;
    }

    char **grid = malloc(H * sizeof(char*));
    for (int i = 0; i < H; i++) {
        grid[i] = malloc(W + 1);
        scanf("%s", grid[i]);
    }

    if (sr < 0 || sr >= H || sc < 0 || sc >= W || tr < 0 || tr >= H || tc < 0 || tc >= W) {
        printf("-1\n");
        for (int i = 0; i < H; i++) free(grid[i]);
        free(grid);
        return 0;
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

    int queue[400];
    int head = 0, tail = 0;

    queue[tail++] = sr * W + sc;

    while (head < tail) {
        int curr = queue[head++];
        int x = curr % W;
        int y = curr / W;

        if (x == tc && y == tr) break;

        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];

            if (nx >= 0 && nx < W && ny >= 0 && ny < H && dist[ny][nx] == -1 && grid[ny][nx] != '#') {
                dist[ny][nx] = dist[y][x] + 1;
                queue[tail++] = ny * W + nx;
            }
        }
    }

    printf("%d\n", dist[tr][tc]);

    for (int i = 0; i < H; i++) free(grid[i]);
    free(grid);
    return 0;
}