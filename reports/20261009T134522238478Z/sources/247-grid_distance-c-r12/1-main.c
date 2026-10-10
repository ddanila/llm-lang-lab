#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int H, W;
    if (scanf("%d %d", &H, &W) != 2) return 0;
    char grid[21][22];
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            grid[i][j] = getchar();
        }
        // consume newline after row
        char c = getchar();
        if (c == '\n') continue;
    }

    int sr, sc, tr, tc;
    scanf("%d %d %d %d", &sr, &sc, &tr, &tc);

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

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    for (int k = 0; k < H * W; k++) {
        for (int r = 0; r < H; r++) {
            for (int c = 0; c < W; c++) {
                if (dist[r][c] != -1) {
                    for (int d = 0; d < 4; d++) {
                        int nr = r + dr[d];
                        int nc = c + dc[d];
                        if (nr >= 0 && nr < H && nc >= 0 && nc < W && grid[nr][nc] == '.') {
                            if (dist[nr][nc] == -1 || dist[nr][nc] > dist[r][c] + 1) {
                                dist[nr][nc] = dist[r][c] + 1;
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