#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int H, W, sr, sc, tr, tc;
    if (scanf("%d %d %d %d %d %d", &H, &W, &sr, &sc, &tr, &tc) != 6) {
        return 0;
    }

    char *grid = malloc(H * sizeof(char) * W);
    if (!grid) return 0;

    for (int i = 0; i < H; i++) {
        fgets(grid + i * W, W + 1, stdin);
        // Remove newline if present
        int len = strlen(grid + i * W);
        while (len > 0 && (grid[i * W + len - 1] == '\n' || grid[i * W + len - 1] == '\r')) {
            grid[i * W + --len] = '\0';
        }
    }

    // Check if start or target is blocked
    if (sr < 0 || sr >= H || sc < 0 || sc >= W || tr < 0 || tr >= H || tc < 0 || tc >= W) {
        printf("-1\n");
        free(grid);
        return 0;
    }

    if (grid[sr * W + sc] == '#' || grid[tr * W + tc] == '#') {
        printf("-1\n");
        free(grid);
        return 0;
    }

    // BFS
    int visited[H][W];
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            visited[i][j] = -1;
        }
    }

    int dq[40000];
    int head = 0, tail = 0;

    dq[tail++] = sr * W + sc;
    visited[sr][sc] = 0;

    int dr[] = {0, 0, 1, -1};
    int dc[] = {1, -1, 0, 0};

    while (head < tail) {
        int curr = dq[head++];
        int r = curr / W;
        int c = curr % W;

        if (r == tr && c == tc) {
            printf("%d\n", visited[r][c]);
            free(grid);
            return 0;
        }

        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k];
            int nc = c + dc[k];

            if (nr >= 0 && nr < H && nc >= 0 && nc < W &&
                grid[nr * W + nc] == '.' && visited[nr][nc] == -1) {
                visited[nr][nc] = visited[r][c] + 1;
                dq[tail++] = nr * W + nc;
            }
        }
    }

    // No path found
    printf("-1\n");
    free(grid);
    return 0;
}