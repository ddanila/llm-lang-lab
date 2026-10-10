#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int H, W;
    if (scanf("%d %d", &H, &W) != 2) return 0;
    int sr, sc, tr, tc;
    scanf("%d %d %d %d", &sr, &sc, &tr, &tc);
    
    char grid[21][21];
    for (int i = 0; i < H; i++) {
        if (scanf("%s", grid[i]) != 1) return 0;
    }
    
    if (grid[sr][sc] == '#' || grid[tr][tc] == '#') {
        printf("-1\n");
        return 0;
    }
    
    int dist[20][20];
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            dist[i][j] = -1;
        }
    }
    dist[sr][sc] = 0;
    
    int dr[] = {0, 0, 1, -1};
    int dc[] = {1, -1, 0, 0};
    
    while (1) {
        int changed = 0;
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                if (dist[i][j] != -1) {
                    for (int k = 0; k < 4; k++) {
                        int ni = i + dr[k];
                        int nj = j + dc[k];
                        if (ni >= 0 && ni < H && nj >= 0 && nj < W) {
                            if (grid[ni][nj] == '.' && dist[ni][nj] == -1) {
                                dist[ni][nj] = dist[i][j] + 1;
                                changed = 1;
                            }
                        }
                    }
                }
            }
        }
        if (!changed) break;
    }
    
    printf("%d\n", dist[tr][tc]);
    return 0;
}