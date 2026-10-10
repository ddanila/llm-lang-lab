#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int H, W, sr, sc, tr, tc;
    if (scanf("%d %d %d %d %d %d", &H, &W, &sr, &sc, &tr, &tc) != 6) return 0;

    char **grid = malloc(H * sizeof(char*));
    for (int i = 0; i < H; i++) {
        grid[i] = malloc(W + 1);
        scanf("%s", grid[i]);
    }

    if (sr < 0 || sr >= H || sc < 0 || sc >= W || tr < 0 || tr >= H || tc < 0 || tc >= W) {
        for (int i = 0; i < H; i++) free(grid[i]);
        free(grid);
        printf("-1\n");
        return 0;
    }

    if (grid[sr][sc] == '#' || grid[tr][tc] == '#') {
        for (int i = 0; i < H; i++) free(grid[i]);
        free(grid);
        printf("-1\n");
        return 0;
    }

    int dist[H][W];
    memset(dist, -1, sizeof(dist));
    int q[H * W + 1], qh = 0, qt = 0;
    
    dist[sr][sc] = 0;
    q[qt++] = sr * W + sc;

    int dr[] = {0, 0, 1, -1};
    int dc[] = {1, -1, 0, 0};

    while (qh < qt) {
        int curr = q[qh++];
        int r = curr / W, c = curr % W;
        int d = dist[r][c];

        if (r == tr && c == tc) break;

        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i], nc = c + dc[i];
            if (nr >= 0 && nr < H && nc >= 0 && nc < W && grid[nr][nc] == '.' && dist[nr][nc] == -1) {
                dist[nr][nc] = d + 1;
                q[qt++] = nr * W + nc;
            }
        }
    }

    for (int i = 0; i < H; i++) free(grid[i]);
    free(grid);

    printf("%d\n", dist[tr][tc]);
    return 0;
}