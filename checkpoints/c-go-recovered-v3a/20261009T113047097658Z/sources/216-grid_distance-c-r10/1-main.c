#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int H, W;
    if (scanf("%d %d", &H, &W) != 2) return 0;
    int sr, sc, tr, tc;
    scanf("%d %d %d %d", &sr, &sc, &tr, &tc);
    
    char *grid = malloc(H * W);
    if (!grid) return 1;
    
    for (int i = 0; i < H; i++) {
        char row[256];
        scanf("%s", row);
        for (int j = 0; j < W; j++) {
            grid[i * W + j] = row[j];
        }
    }
    
    if (grid[sr * W + sc] == '#' || grid[tr * W + tc] == '#') {
        printf("-1\n");
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
    
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};
    
    while (1) {
        int changed = 0;
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                if (dist[i][j] != -1) {
                    for (int k = 0; k < 4; k++) {
                        int ni = i + dx[k];
                        int nj = j + dy[k];
                        if (ni >= 0 && ni < H && nj >= 0 && nj < W && grid[ni * W + nj] == '#' && dist[ni][nj] == -1) {
                            // Blocked, skip
                        } else if (grid[ni * W + nj] != '#' && dist[ni][nj] == -1) {
                            dist[ni][nj] = dist[i][j] + 1;
                            changed = 1;
                        }
                    }
                }
            }
        }
        if (!changed) break;
    }
    
    int result = dist[tr][tc];
    printf("%d\n", result);
    
    free(grid);
    return 0;
}