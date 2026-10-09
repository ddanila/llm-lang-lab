#include <stdio.h>
#include <string.h>

int main(void) {
    int H, W;
    if (scanf("%d %d", &H, &W) != 2) return 0;
    int sr, sc, tr, tc;
    scanf("%d %d %d %d", &sr, &sc, &tr, &tc);

    char grid[21][21];
    for (int i = 0; i < H; i++) {
        if (fgets(grid[i], sizeof(grid[i]), stdin) == NULL) break;
        size_t len = strlen(grid[i]);
        while (len > 0 && (grid[i][len-1] == '\n' || grid[i][len-1] == '\r')) {
            grid[i][len-1] = '\0';
            len--;
        }
    }

    if (sr < 0 || sr >= H || sc < 0 || sc >= W || tr < 0 || tr >= H || tc < 0 || tc >= W) {
        printf("-1\n");
        return 0;
    }

    if (grid[sr][sc] == '#' || grid[tr][tc] == '#') {
        printf("-1\n");
        return 0;
    }

    if (sr == tr && sc == tc) {
        printf("0\n");
        return 0;
    }

    int dist[21][21];
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            dist[i][j] = -1;
        }
    }

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    int q[400];
    int head = 0, tail = 0;

    q[tail++] = sr * W + sc;
    dist[sr][sc] = 0;

    while (head < tail) {
        int curr = q[head++];
        int r = curr / W;
        int c = curr % W;
        int d = dist[r][c];

        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k];
            int nc = c + dc[k];
            if (nr >= 0 && nr < H && nc >= 0 && nc < W && grid[nr][nc] == '.' && dist[nr][nc] == -1) {
                dist[nr][nc] = d + 1;
                q[tail++] = nr * W + nc;
            }
        }
    }

    printf("%d\n", dist[tr][tc]);

    return 0;
}