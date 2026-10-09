#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int x, y;
} Point;

int main(void) {
    int H, W;
    if (scanf("%d %d", &H, &W) != 2) return 0;
    
    char **grid = malloc(H * sizeof(char*));
    for (int i = 0; i < H; i++) {
        grid[i] = malloc((W + 1) * sizeof(char));
        scanf("%s", grid[i]);
    }
    
    int sr, sc, tr, tc;
    scanf("%d %d %d %d", &sr, &sc, &tr, &tc);
    
    if (grid[sr][sc] == '#' || grid[tr][tc] == '#') {
        printf("-1\n");
        for (int i = 0; i < H; i++) free(grid[i]);
        free(grid);
        return 0;
    }
    
    if (sr == tr && sc == tc) {
        printf("0\n");
        for (int i = 0; i < H; i++) free(grid[i]);
        free(grid);
        return 0;
    }
    
    int dist[20][20];
    memset(dist, -1, sizeof(dist));
    Point q[400];
    int head = 0, tail = 0;
    
    q[tail++] = (Point){sc, sr};
    dist[sr][sc] = 0;
    
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};
    
    while (head < tail) {
        Point curr = q[head++];
        int d = dist[curr.y][curr.x];
        
        for (int i = 0; i < 4; i++) {
            int nx = curr.x + dx[i];
            int ny = curr.y + dy[i];
            
            if (nx >= 0 && nx < W && ny >= 0 && ny < H) {
                if (grid[ny][nx] == '.' && dist[ny][nx] == -1) {
                    dist[ny][nx] = d + 1;
                    q[tail++] = (Point){nx, ny};
                    if (nx == tc && ny == tr) break;
                }
            }
        }
    }
    
    printf("%d\n", dist[tr][tc]);
    
    for (int i = 0; i < H; i++) free(grid[i]);
    free(grid);
    
    return 0;
}