#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int H, W, sr, sc, tr, tc;
    if (scanf("%d %d %d %d %d %d", &H, &W, &sr, &sc, &tr, &tc) != 6) return 0;

    // Consume the newline after scanf
    getchar();

    char *grid = malloc(H * W);
    if (!grid) return 1;

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            grid[i * W + j] = getchar();
        }
    }

    // Check if start or target is blocked
    if (grid[sr * W + sc] == '#' || grid[tr * W + tc] == '#') {
        printf("-1\n");
        free(grid);
        return 0;
    }

    // BFS
    int *dist = calloc(H * W, sizeof(int));
    if (!dist) {
        free(grid);
        return 1;
    }
    for (int i = 0; i < H * W; i++) dist[i] = -1;

    int q[400];
    int head = 0, tail = 0;
    q[tail++] = sr * W + sc;
    dist[sr * W + sc] = 0;

    int dr[] = {1, -1, 0, 0};
    int dc[] = {0, 0, 1, -1};

    while (head < tail) {
        int curr = q[head++];
        int r = curr / W;
        int c = curr % W;

        if (r == tr && c == tc) break;

        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k];
            int nc = c + dc[k];
            if (nr >= 0 && nr < H && nc >= 0 && nc < W && grid[nr * W + nc] == '.' && dist[nr * W + nc] == -1) {
                dist[nr * W + nc] = dist[curr] + 1;
                q[tail++] = nr * W + nc;
            }
        }
    }

    printf("%d\n", dist[tr * W + tc]);

    free(grid);
    free(dist);
    return 0;
}