package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	
	// Read H W sr sc tr tc
	line1, err := reader.ReadString('\n')
	if err != nil {
		return
	}
	line1 = strings.TrimSpace(line1)
	parts := strings.Fields(line1)
	if len(parts) < 6 {
		return
	}
	
	H, W, sr, sc, tr, tc := parseInt(parts[0]), parseInt(parts[1]), parseInt(parts[2]), parseInt(parts[3]), parseInt(parts[4]), parseInt(parts[5])
	
	// Read grid
	grid := make([]string, H)
	for i := 0; i < H; i++ {
		line, err := reader.ReadString('\n')
		if err != nil {
			return
		}
		grid[i] = strings.TrimRight(line, "\r\n")
	}
	
	// Check if start or end is blocked
	if sr >= H || sc >= W || grid[sr][sc] == '#' {
		fmt.Println("-1")
		return
	}
	if tr >= H || tc >= W || grid[tr][tc] == '#' {
		fmt.Println("-1")
		return
	}
	
	// BFS
	dist := make([][]int, H)
	for i := range dist {
		dist[i] = make([]int, W)
		for j := range dist[i] {
			dist[i][j] = -1
		}
	}
	
	queue := [][2]int{[2]int{sr, sc}}
	dist[sr][sc] = 0
	
	head := 0
	for head < len(queue) {
		curr := queue[head]
	head++
		
		r, c := curr[0], curr[1]
		d := dist[r][c]
		
		// Directions: up, down, left, right
		dirs := [][2]int{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}
		
		for _, dir := range dirs {
			nr, nc := r+dir[0], c+dir[1]
			
			if nr >= 0 && nr < H && nc >= 0 && nc < W && grid[nr][nc] != '#' && dist[nr][nc] == -1 {
				dist[nr][nc] = d + 1
				queue = append(queue, [2]int{nr, nc})
			}
		}
	}
	
	fmt.Println(dist[tr][tc])
}

func parseInt(s string) int {
	i := 0
	for _, c := range s {
		if c >= '0' && c <= '9' {
			i = i*10 + int(c-'0')
		} else {
			break
		}
	}
	return i
}