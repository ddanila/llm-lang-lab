package main

import (
	"fmt"
	"bufio"
	"strings"
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	
	line, err := reader.ReadString('\n')
	if err != nil {
		return
	}
	line = strings.TrimSpace(line)
	parts := strings.Fields(line)
	if len(parts) < 4 {
		return
	}
	
	H, W, sr, sc, tr, tc := 0, 0, 0, 0, 0, 0
	fmt.Sscanf(line, "%d %d %d %d %d %d", &H, &W, &sr, &sc, &tr, &tc)
	
	grid := make([]string, H)
	for i := 0; i < H; i++ {
		line, _ = reader.ReadString('\n')
		grid[i] = line[:len(line)-1] // remove newline
	}
	
	if sr >= H || sc >= W || tr >= H || tc >= W {
		fmt.Println(-1)
		return
	}
	
	if grid[sr][sc] == '#' || grid[tr][tc] == '#' {
		fmt.Println(-1)
		return
	}
	
	queue := [][2]int{sr, sc}
	dist := make([][]int, H)
	for i := range dist {
		dist[i] = make([]int, W)
	}
	dist[sr][sc] = 0
	
	head := 0
	tail := 1
	
	dx := []int{-1, 1, 0, 0}
	dy := []int{0, 0, -1, 1}
	
	for head < tail {
		x, y := queue[head]
		head++
		
		if x == tr && y == tc {
			fmt.Println(dist[x][y])
			return
		}
		
		for k := 0; k < 4; k++ {
			nx, ny := x+dx[k], y+dy[k]
			if nx >= 0 && nx < H && ny >= 0 && ny < W && grid[nx][ny] != '#' && dist[nx][ny] == -1 {
				dist[nx][ny] = dist[x][y] + 1
				queue[tail] = [2]int{nx, ny}
				tail++
			}
		}
	}
	
	fmt.Println(-1)
}