#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int H, W;
    if (scanf("%d %d", &H, &W) != 2) return 0;
    
    char *grid = malloc(H * sizeof(char));
    for (int i = 0; i < H; i++) {
        grid[i] = getchar();
        while (grid[i] == '\n' || grid[i] == ' ') {
            grid[i] = getchar();
        }
    }
    
    int sr, sc, tr, tc;
    if (scanf("%d %d %d %d", &sr, &sc, &tr, &tc) != 4) {
        free(grid);
        return 0;
    }
    
    // Read remaining characters on the line after sr sc tr tc
    char c = getchar();
    while (c == '\n' || c == ' ') {
        c = getchar();
    }
    
    int dist[H][W];
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            dist[i][j] = -1;
        }
    }
    
    // Check if start or end is blocked
    if (grid[sr][sc] == '#' || grid[tr][tc] == '#') {
        printf("-1\n");
        free(grid);
        return 0;
    }
    
    // BFS
    int q[H * W];
    int head = 0, tail = 0;
    q[tail++] = sr * W + sc;
    dist[sr][sc] = 0;
    
    int dr[] = {1, -1, 0, 0};
    int dc[] = {0, 0, 1, -1};
    
    while (head < tail) {
        int cur = q[head++];
        int r = cur / W;
        int c_idx = cur % W;
        
        if (r == tr && c_idx == tc) {
            printf("%d\n", dist[r][c_idx]);
            free(grid);
            return 0;
        }
        
        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c_idx + dc[i];
            
            if (nr >= 0 && nr < H && nc >= 0 && nc < W && grid[nr][nc] != '#' && dist[nr][nc] == -1) {
                dist[nr][nc] = dist[r][c_idx] + 1;
                q[tail++] = nr * W + nc;
            }
        }
    }
    
    // If we exit BFS without finding the target, it means no path exists
    printf("-1\n");
    free(grid);
    return 0;
}