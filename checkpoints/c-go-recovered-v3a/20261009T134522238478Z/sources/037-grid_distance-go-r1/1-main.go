package main

import (
	"fmt"
	"bufio"
)

func main() {
	reader := bufio.NewReader(nil) // We'll use fmt.Scan for simplicity, but need to handle lines properly
	
	// Read H and W
	var H, W int
	if _, err := fmt.Scanf("%d %d", &H, &W); err != nil {
		return
	}
	
	// Read sr, sc, tr, tc
	var sr, sc, tr, tc int
	if _, err := fmt.Scanf("%d %d %d %d", &sr, &sc, &tr, &tc); err != nil {
		return
	}
	
	// Read grid
	grid := make([]string, H)
	for i := 0; i < H; i++ {
		var line string
		if _, err := fmt.Scanf("%s", &line); err != nil {
			return
		}
		grid[i] = line
	}
	
	// Check if start or end is blocked
	if grid[sr][sc] == '#' || grid[tr][tc] == '#' {
		fmt.Println("-1")
		return
	}
	
	// BFS
	queue := [][2]int{{sr, sc}}
	dist := make([][]int, H)
	for i := range dist {
		dist[i] = make([]int, W)
		for j := range dist[i] {
			dist[i][j] = -1
		}
	}
	
	dist[sr][sc] = 0
	
	dx := []int{0, 0, 1, -1}
	dy := []int{1, -1, 0, 0}
	
	for len(queue) > 0 {
		curr := queue[0]
		queue = queue[1:]
		
		x, y := curr[0], curr[1]
		d := dist[x][y]
		
		if x == tr && y == tc {
			fmt.Println(d)
			return
		}
		
		for i := 0; i < 4; i++ {
			nx, ny := x+dx[i], y+dy[i]
			if nx >= 0 && nx < H && ny >= 0 && ny < W && grid[nx][ny] == '.' && dist[nx][ny] == -1 {
				dist[nx][ny] = d + 1
				queue = append(queue, [2]int{nx, ny})
			}
		}
	}
	
	fmt.Println("-1")
}