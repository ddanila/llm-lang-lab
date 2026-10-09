#include <stdio.h>
#include <stdlib.h>

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
        // consume the newline after each row
        int c = getchar();
        if (c == '\n') continue;
    }

    if (sr < 0 || sr >= H || sc < 0 || sc >= W || tr < 0 || tr >= H || tc < 0 || tc >= W) {
        printf("-1\n");
        return 0;
    }

    if (grid[sr][sc] == '#' || grid[tr][tc] == '#') {
        printf("-1\n");
        return 0;
    }

    int dist[25][25];
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            dist[i][j] = -1;
        }
    }

    int q[25 * 25];
    int head = 0, tail = 0;

    q[tail++] = sr * W + sc;
    dist[sr][sc] = 0;

    int dr[] = {1, -1, 0, 0};
    int dc[] = {0, 0, 1, -1};

    while (head < tail) {
        int u = q[head++];
        int r = u / W;
        int c = u % W;
        int d = dist[r][c];

        if (r == tr && c == tc) {
            printf("%d\n", d);
            return 0;
        }

        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k];
            int nc = c + dc[k];
            if (nr >= 0 && nr < H && nc >= 0 && nc < W) {
                if (grid[nr][nc] != '#' && dist[nr][nc] == -1) {
                    dist[nr][nc] = d + 1;
                    q[tail++] = nr * W + nc;
                }
            }
        }
    }

    printf("-1\n");
    return 0;
}