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

    if (grid[sr][sc] == '#' || grid[tr][tc] == '#') {
        printf("-1\n");
        for (int i = 0; i < H; i++) free(grid[i]);
        free(grid);
        return 0;
    }

    int dist[H][W];
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            dist[i][j] = -1;
        }
    }
    dist[sr][sc] = 0;

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    for (int d = 0; d < H * W && (dist[tr][tc] == -1); d++) {
        // BFS using a simple queue simulation with arrays
        int q[H * W];
        int head = 0, tail = 0;

        // Rebuild queue from current visited nodes
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                if (dist[i][j] != -1) {
                    q[tail++] = i * W + j;
                }
            }
        }

        int new_head = head, new_tail = tail;
        while (new_head < new_tail && dist[tr][tc] == -1) {
            int curr = q[new_head++];
            int r = curr / W;
            int c = curr % W;
            int dcur = dist[r][c];

            for (int k = 0; k < 4; k++) {
                int nr = r + dr[k];
                int nc = c + dc[k];
                if (nr >= 0 && nr < H && nc >= 0 && nc < W && grid[nr][nc] == '.' && dist[nr][nc] == -1) {
                    dist[nr][nc] = dcur + 1;
                }
            }
        }
    }

    printf("%d\n", dist[tr][tc]);

    for (int i = 0; i < H; i++) free(grid[i]);
    free(grid);
    return 0;
}