#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int H, W, sr, sc, tr, tc;
    if (scanf("%d %d %d %d %d %d", &H, &W, &sr, &sc, &tr, &tc) != 6) return 0;

    char **grid = malloc(H * sizeof(char *));
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

    int *dist = calloc(H * W, sizeof(int));
    for (int i = 0; i < H * W; i++) dist[i] = -1;

    int queue[400];
    int head = 0, tail = 0;

    queue[tail++] = sr * W + sc;
    dist[sr * W + sc] = 0;

    int dr[] = {1, -1, 0, 0};
    int dc[] = {0, 0, 1, -1};

    while (head < tail) {
        int curr = queue[head++];
        int r = curr / W;
        int c = curr % W;

        if (r == tr && c == tc) break;

        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k];
            int nc = c + dc[k];

            if (nr >= 0 && nr < H && nc >= 0 && nc < W && grid[nr][nc] == '#' && dist[nr * W + nc] != -1) continue;

            if (dist[nr * W + nc] != -1) continue;

            dist[nr * W + nc] = dist[r * W + c] + 1;
            queue[tail++] = nr * W + nc;
        }
    }

    printf("%d\n", dist[tr * W + tc]);

    for (int i = 0; i < H * W; i++) free(grid[i]);
    free(grid);
    return 0;
}