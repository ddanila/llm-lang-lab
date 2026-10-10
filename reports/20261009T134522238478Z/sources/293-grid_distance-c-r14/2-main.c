#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int H, W;
    if (scanf("%d %d", &H, &W) != 2) return 0;
    
    char **grid = malloc(H * sizeof(char*));
    for (int i = 0; i < H; i++) {
        grid[i] = malloc(W + 1);
        scanf("%s", grid[i]);
    }
    
    int sr, sc, tr, tc;
    if (scanf("%d %d %d %d", &sr, &sc, &tr, &tc) != 4) {
        for (int i = 0; i < H; i++) free(grid[i]);
        free(grid);
        return 0;
    }
    
    if (grid[sr][sc] == '#' || grid[tr][tc] == '#') {
        for (int i = 0; i < H; i++) free(grid[i]);
        free(grid);
        printf("-1\n");
        return 0;
    }
    
    int dist[H][W];
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            dist[i][j] = -1;
        }
    }
    
    if (sr == tr && sc == tc) {
        printf("0\n");
        for (int i = 0; i < H; i++) free(grid[i]);
        free(grid);
        return 0;
    }
    
    int q[H * W];
    int head = 0, tail = 0;
    
    q[tail++] = sr * W + sc;
    dist[sr][sc] = 0;
    
    int dr[] = {1, -1, 0, 0};
    int dc[] = {0, 0, 1, -1};
    
    while (head < tail) {
        int curr = q[head++];
        int r = curr / W;
        int c = curr % W;
        
        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k];
            int nc = c + dc[k];
            
            if (nr >= 0 && nr < H && nc >= 0 && nc < W) {
                if (grid[nr][nc] == '.' && dist[nr][nc] == -1) {
                    dist[nr][nc] = dist[r][c] + 1;
                    q[tail++] = nr * W + nc;
                    
                    if (nr == tr && nc == tc) {
                        printf("%d\n", dist[tr][tc]);
                        for (int i = 0; i < H; i++) free(grid[i]);
                        free(grid);
                        return 0;
                    }
                }
            }
        }
    }
    
    printf("-1\n");
    for (int i = 0; i < H; i++) free(grid[i]);
    free(grid);
    return 0;
}