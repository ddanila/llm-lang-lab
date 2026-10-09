#include <stdio.h>
#include <string.h>

int main(void) {
    int H, W;
    if (scanf("%d %d", &H, &W) != 2) return 0;
    int sr, sc, tr, tc;
    scanf("%d %d %d %d", &sr, &sc, &tr, &tc);

    char grid[25][25];
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            grid[i][j] = getchar();
        }
    }

    if (grid[sr][sc] == '#' || grid[tr][tc] == '#') {
        printf("-1\n");
        return 0;
    }

    int dist[25][25];
    memset(dist, -1, sizeof(dist));
    int q[100], qx = 0, qy = 0;

    dist[sr][sc] = 0;
    q[qx++] = sr * W + sc;

    int dr[] = {0, 0, 1, -1};
    int dc[] = {1, -1, 0, 0};

    while (qx <= qy) {
        int curr = q[qy++];
        int r = curr / W;
        int c = curr % W;
        int d = dist[r][c];

        if (r == tr && c == tc) break;

        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k];
            int nc = c + dc[k];

            if (nr >= 0 && nr < H && nc >= 0 && nc < W &&
                grid[nr][nc] == '.' && dist[nr][nc] == -1) {
                dist[nr][nc] = d + 1;
                q[qx++] = nr * W + nc;
            }
        }
    }

    printf("%d\n", dist[tr][tc]);
    return 0;
}