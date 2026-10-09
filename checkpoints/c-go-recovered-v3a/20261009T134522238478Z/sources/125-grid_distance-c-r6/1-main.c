#include <stdio.h>
#include <string.h>

int main(void) {
    int H, W, sr, sc, tr, tc;
    if (scanf("%d %d %d %d %d %d", &H, &W, &sr, &sc, &tr, &tc) != 6) return 0;

    char grid[21][22];
    for (int i = 0; i < H; i++) {
        if (scanf("%s", grid[i]) != 1) return 0;
    }

    // Validate endpoints
    if (grid[sr][sc] == '#' || grid[tr][tc] == '#') {
        printf("-1\n");
        return 0;
    }

    int dist[21][22];
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            dist[i][j] = -1;
        }
    }
    dist[sr][sc] = 0;

    int dr[] = {0, 0, 1, -1};
    int dc[] = {1, -1, 0, 0};

    for (int d = 0; d < H * W; d++) {
        for (int r = 0; r < H; r++) {
            for (int c = 0; c < W; c++) {
                if (dist[r][c] == -1) continue;
                for (int k = 0; k < 4; k++) {
                    int nr = r + dr[k];
                    int nc = c + dc[k];
                    if (nr >= 0 && nr < H && nc >= 0 && nc < W && grid[nr][nc] == '.' && dist[nr][nc] == -1) {
                        dist[nr][nc] = dist[r][c] + 1;
                    }
                }
            }
        }
    }

    printf("%d\n", dist[tr][tc]);
    return 0;
}