#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int H, W;
    if (scanf("%d %d", &H, &W) != 2) return 0;
    
    char grid[20][21];
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            grid[i][j] = getchar();
        }
        if (i < H) getchar(); // consume newline after each row
    }
    
    int sr, sc, tr, tc;
    scanf("%d %d %d %d", &sr, &sc, &tr, &tc);
    
    if (sr < 0 || sr >= H || sc < 0 || sc >= W || 
        tr < 0 || tr >= H || tc < 0 || tc >= W) {
        printf("-1\n");
        return 0;
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
    
    // BFS
    int q[400];
    int head = 0, tail = 0;
    
    q[tail++] = sr * W + sc;
    dist[sr][sc] = 0;
    
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
            
            if (nr >= 0 && nr < H && nc >= 0 && nc < W && 
                grid[nr][nc] == '.' && dist[nr][nc] == -1) {
                dist[nr][nc] = dist[r][c] + 1;
                q[tail++] = nr * W + nc;
            }
        }
    }
    
    printf("%d\n", dist[tr][tc]);
    
    return 0;
}