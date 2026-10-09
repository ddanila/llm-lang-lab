#include <stdio.h>
#include <string.h>

int main(void) {
    int H, W;
    if (scanf("%d %d", &H, &W) != 2) return 0;
    int sr, sc, tr, tc;
    scanf("%d %d %d %d", &sr, &sc, &tr, &tc);

    char grid[21][22];
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            grid[i][j] = getchar();
            while (grid[i][j] == '\n' || grid[i][j] == ' ') {
                grid[i][j] = getchar();
            }
        }
    }

    if (grid[sr][sc] == '#' || grid[tr][tc] == '#') {
        printf("-1\n");
        return 0;
    }

    int dist[21][21];
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            dist[i][j] = -1;
        }
    }
    dist[sr][sc] = 0;

    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    for (int d = 0; d < H * W; d++) {
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                if (dist[i][j] != -1) {
                    int nd = dist[i][j] + 1;
                    for (int k = 0; k < 4; k++) {
                        int ni = i + dx[k];
                        int nj = j + dy[k];
                        if (ni >= 0 && ni < H && nj >= 0 && nj < W) {
                            if (grid[ni][nj] == '.' && dist[ni][nj] == -1) {
                                dist[ni][nj] = nd;
                            }
                        }
                    }
                }
            }
        }
    }

    printf("%d\n", dist[tr][tc]);
    return 0;
}