#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int H, W;
    if (scanf("%d %d", &H, &W) != 2) return 0;
    
    char *grid = malloc(H * sizeof(char));
    for (int i = 0; i < H; i++) {
        grid[i] = getchar();
    }
    
    int sr, sc, tr, tc;
    scanf("%d %d %d %d", &sr, &sc, &tr, &tc);
    
    if (grid[sr * W + sc] == '#' || grid[tr * W + tc] == '#') {
        printf("-1\n");
        return 0;
    }
    
    int dist[H][W];
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            dist[i][j] = -1;
        }
    }
    dist[sr][sc] = 0;
    
    int q[400];
    int head = 0, tail = 0;
    q[tail++] = sr * W + sc;
    
    int dx[] = {0, 1, 0, -1};
    int dy[] = {1, 0, -1, 0};
    
    while (head < tail) {
        int curr = q[head++];
        int cx = curr % W;
        int cy = curr / W;
        
        if (cx == tc && cy == tr) break;
        
        for (int k = 0; k < 4; k++) {
            int nx = cx + dx[k];
            int ny = cy + dy[k];
            
            if (nx >= 0 && nx < H && ny >= 0 && ny < W) {
                if (grid[nx * W + ny] == '.' && dist[nx][ny] == -1) {
                    dist[nx][ny] = dist[cy][cx] + 1;
                    q[tail++] = nx * W + ny;
                }
            }
        }
    }
    
    printf("%d\n", dist[tr][tc]);
    
    free(grid);
    return 0;
}