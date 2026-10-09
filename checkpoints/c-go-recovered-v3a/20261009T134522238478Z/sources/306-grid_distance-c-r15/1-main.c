#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int H, W, sr, sc, tr, tc;
    if (scanf("%d %d %d %d %d %d", &H, &W, &sr, &sc, &tr, &tc) != 6) return 0;

    char **grid = malloc(H * sizeof(char *));
    for (int i = 0; i < H; i++) {
        grid[i] = malloc(W + 1);
        scanf("%s", grid[i]);
    }

    // Check if endpoints are blocked
    if (grid[sr][sc] == '#' || grid[tr][tc] == '#') {
        for (int i = 0; i < H; i++) free(grid[i]);
        free(grid);
        printf("-1\n");
        return 0;
    }

    // BFS
    int dist[H][W];
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            dist[i][j] = -1;
        }
    }
    dist[sr][sc] = 0;

    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    // Use a simple array as queue since H,W <= 20
    int qx[H * W], qy[H * W];
    int head = 0, tail = 0;
    qx[tail] = sr;
    qy[tail] = sc;
    tail++;

    while (head < tail) {
        int x = qx[head];
        int y = qy[head];
        head++;

        int d = dist[x][y];
        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];

            if (nx >= 0 && nx < H && ny >= 0 && ny < W && grid[nx][ny] == '#' && dist[nx][ny] != -1) continue;

            if (dist[nx][ny] != -1) continue;

            dist[nx][ny] = d + 1;
            qx[tail] = nx;
            qy[tail] = ny;
            tail++;
        }
    }

    int result = dist[tr][tc];
    for (int i = 0; i < H; i++) free(grid[i]);
    free(grid);

    printf("%d\n", result);
    return 0;
}