#include <stdio.h>
#include <string.h>

int main(void) {
    int H, W;
    if (scanf("%d %d", &H, &W) != 2) return 0;
    int sr, sc, tr, tc;
    scanf("%d %d %d %d", &sr, &sc, &tr, &tc);

    char grid[21][22];
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            grid[i][j] = getchar();
        }
        // Skip any whitespace/newlines after reading W chars
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}
    }

    // Check if start or end is blocked
    if (grid[sr][sc] == '#' || grid[tr][tc] == '#') {
        printf("-1\n");
        return 0;
    }

    // BFS
    int dist[21][21];
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            dist[i][j] = -1;
        }
    }
    dist[sr][sc] = 0;

    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    int queue[400];
    int head = 0;
    int tail = 0;
    queue[tail++] = sr * W + sc;

    while (head < tail) {
        int curr = queue[head++];
        int x = curr % W;
        int y = curr / W;

        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];

            if (nx >= 0 && nx < H && ny >= 0 && ny < W) {
                if (grid[ny][nx] != '#' && dist[ny][nx] == -1) {
                    dist[ny][nx] = dist[y][x] + 1;
                    queue[tail++] = ny * W + nx;
                }
            }
        }
    }

    printf("%d\n", dist[tr][tc]);
    return 0;
}