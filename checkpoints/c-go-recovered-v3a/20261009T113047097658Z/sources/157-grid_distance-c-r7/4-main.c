#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_H 20
#define MAX_W 20

int dist[MAX_H][MAX_W];
int visited[MAX_H][MAX_W];
char grid[MAX_H][MAX_W];
int dr[] = {1, -1, 0, 0};
int dc[] = {0, 0, 1, -1};

void bfs(int sr, int sc, int tr, int tc) {
    // Initialize visited and dist arrays
    for (int i = 0; i < MAX_H; i++) {
        for (int j = 0; j < MAX_W; j++) {
            dist[i][j] = -1;
            visited[i][j] = 0;
        }
    }

    // Check if start or end is blocked
    if (grid[sr][sc] == '#' || grid[tr][tc] == '#') {
        printf("-1\n");
        return;
    }

    // Same position - distance is 0
    if (sr == tr && sc == tc) {
        printf("0\n");
        return;
    }

    int q[MAX_H * MAX_W];
    int head = 0, tail = 0;

    visited[sr][sc] = 1;
    dist[sr][sc] = 0;
    q[tail++] = sr * MAX_W + sc;

    while (head < tail) {
        int curr = q[head++];
        int r = curr / MAX_W;
        int c = curr % MAX_W;

        // Check if we reached target
        if (r == tr && c == tc) {
            printf("%d\n", dist[r][c]);
            return;
        }

        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k];
            int nc = c + dc[k];

            if (nr >= 0 && nr < MAX_H && nc >= 0 && nc < MAX_W) {
                if (!visited[nr][nc] && grid[nr][nc] != '#') {
                    visited[nr][nc] = 1;
                    dist[nr][nc] = dist[r][c] + 1;
                    q[tail++] = nr * MAX_W + nc;
                }
            }
        }
    }

    // No path found
    printf("-1\n");
}

int main() {
    int H, W, sr, sc, tr, tc;
    if (scanf("%d %d", &H, &W) != 2) return 0;
    scanf("%d %d %d %d", &sr, &sc, &tr, &tc);

    // Consume any remaining whitespace including newline
    int c = getchar();
    
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            // Read until we get a non-whitespace character or EOF
            while ((c = getchar()) != EOF && (c == '\n' || c == ' ' || c == '\r')) {}
            if (c != EOF) {
                grid[i][j] = c;
            }
        }
    }

    bfs(sr, sc, tr, tc);

    return 0;
}