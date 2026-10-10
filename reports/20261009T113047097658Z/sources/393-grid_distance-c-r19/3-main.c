#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int H, W;
    if (scanf("%d %d", &H, &W) != 2) return 0;
    int sr, sc, tr, tc;
    scanf("%d %d %d %d", &sr, &sc, &tr, &tc);

    char *grid = malloc(H * W + 1);
    if (!grid) return 1;
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            char c;
            scanf("%c", &c);
            grid[i * W + j] = c;
        }
    }
    grid[H * W] = '\0';

    if (grid[sr * W + sc] == '#' || grid[tr * W + tc] == '#') {
        printf("-1\n");
        free(grid);
        return 0;
    }

    // BFS
    int dist[H][W];
    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++)
            dist[i][j] = -1;

    int qx[400], qy[400];
    int head = 0, tail = 0;
    qx[tail] = sr;
    qy[tail] = sc;
    tail++;
    dist[sr][sc] = 0;

    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};

    while (head < tail) {
        int x = qx[head];
        int y = qy[head];
        head++;

        if (x == tr && y == tc) break;

        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];

            if (nx >= 0 && nx < H && ny >= 0 && ny < W &&
                dist[nx][ny] == -1 && grid[nx * W + ny] != '#') {
                dist[nx][ny] = dist[x][y] + 1;
                qx[tail] = nx;
                qy[tail] = ny;
                tail++;
            }
        }
    }

    printf("%d\n", dist[tr][tc]);
    free(grid);
    return 0;
}