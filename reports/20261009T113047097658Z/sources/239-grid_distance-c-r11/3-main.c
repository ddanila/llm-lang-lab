#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_H 20
#define MAX_W 20

int main(void) {
    int H, W;
    if (scanf("%d %d", &H, &W) != 2) return 0;
    
    char grid[MAX_H][MAX_W];
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            int c = getchar();
            while (c == '\n' || c == ' ') c = getchar();
            grid[i][j] = c;
        }
    }
    
    int sr, sc, tr, tc;
    if (scanf("%d %d %d %d", &sr, &sc, &tr, &tc) != 4) return 0;
    
    // Check if start or end is blocked
    if (grid[sr][sc] == '#' || grid[tr][tc] == '#') {
        printf("-1\n");
        return 0;
    }
    
    // BFS
    int dist[MAX_H][MAX_W];
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            dist[i][j] = -1;
        }
    }
    
    int dr[] = {1, -1, 0, 0};
    int dc[] = {0, 0, 1, -1};
    
    // Queue for BFS: encode (r, c) as r * W + c
    int queue[400];
    int head = 0, tail = 0;
    
    queue[tail++] = sr * W + sc;
    dist[sr][sc] = 0;
    
    while (head < tail) {
        int curr = queue[head++];
        int r = curr / W;
        int c = curr % W;
        
        if (r == tr && c == tc) {
            printf("%d\n", dist[r][c]);
            return 0;
        }
        
        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            
            if (nr >= 0 && nr < H && nc >= 0 && nc < W) {
                if (grid[nr][nc] == '.' && dist[nr][nc] == -1) {
                    dist[nr][nc] = dist[r][c] + 1;
                    queue[tail++] = nr * W + nc;
                }
            }
        }
    }
    
    // If target not reached or no path
    printf("-1\n");
    return 0;
}