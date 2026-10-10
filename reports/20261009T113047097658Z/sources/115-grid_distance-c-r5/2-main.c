#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int H, W;
    if (scanf("%d %d", &H, &W) != 2) return 0;
    int sr, sc, tr, tc;
    scanf("%d %d %d %d", &sr, &sc, &tr, &tc);
    
    char *grid = malloc(H * W + 1);
    for (int i = 0; i < H; i++) {
        if (fgets(&grid[i*W], W + 1, stdin) == NULL) break;
    }
    
    int blocked[20][20];
    memset(blocked, 0, sizeof(blocked));
    
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (grid[i*W + j] == '#') {
                blocked[i][j] = 1;
            }
        }
    }
    
    if (blocked[sr][sc] || blocked[tr][tc]) {
        printf("-1\n");
        free(grid);
        return 0;
    }
    
    if (sr == tr && sc == tc) {
        printf("0\n");
        free(grid);
        return 0;
    }
    
    int dist[20][20];
    memset(dist, -1, sizeof(dist));
    
    int q[400];
    int head = 0, tail = 0;
    
    q[tail++] = sr * W + sc;
    dist[sr][sc] = 0;
    
    int dr[] = {0, 1, 0, -1};
    int dc[] = {1, 0, -1, 0};
    
    while (head < tail) {
        int curr = q[head++];
        int r = curr / W;
        int c = curr % W;
        
        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k];
            int nc = c + dc[k];
            
            if (nr >= 0 && nr < H && nc >= 0 && nc < W) {
                if (!blocked[nr][nc] && dist[nr][nc] == -1) {
                    dist[nr][nc] = dist[r][c] + 1;
                    q[tail++] = nr * W + nc;
                }
            }
        }
    }
    
    printf("%d\n", dist[tr][tc]);
    free(grid);
    return 0;
}