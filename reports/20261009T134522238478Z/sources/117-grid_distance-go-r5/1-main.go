package main

import (
	"fmt"
	"bufio"
	"strings"
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	
	// Read H W
	line1, err := reader.ReadString('\n')
	if err != nil {
		return
	}
	line1 = strings.TrimSpace(line1)
	parts := strings.Fields(line1)
	H, _ := strconv.Atoi(parts[0])
	W, _ := strconv.Atoi(parts[1])
	
	// Read sr sc tr tc
	line2, _ := reader.ReadString('\n')
	line2 = strings.TrimSpace(line2)
	parts = strings.Fields(line2)
	sr, _ := strconv.Atoi(parts[0])
	sc, _ := strconv.Atoi(parts[1])
	tr, _ := strconv.Atoi(parts[2])
	tc, _ := strconv.Atoi(parts[3])
	
	// Read grid
	grid := make([]string, H)
	for i := 0; i < H; i++ {
		line, _ := reader.ReadString('\n')
		grid[i] = strings.TrimSpace(line)
	}
	
	// Check if start or end is blocked
	if sr >= H || sc >= W || tr >= H || tc >= W {
		fmt.Println("-1")
		return
	}
	if grid[sr][sc] == '#' || grid[tr][tc] == '#' {
		fmt.Println("-1")
		return
	}
	
	// BFS
	dist := make([][]int, H)
	for i := 0; i < H; i++ {
		dist[i] = make([]int, W)
		for j := 0; j < W; j++ {
			dist[i][j] = -1
		}
	}
	
	queue := []Pos{{sr, sc}}
	dist[sr][sc] = 0
	
	for len(queue) > 0 {
		current := queue[0]
		queue = queue[1:]
		
		d := dist[current.r][current.c]
		
		// Check up
		if current.r-1 >= 0 && grid[current.r-1][current.c] == '.' && dist[current.r-1][current.c] == -1 {
			dist[current.r-1][current.c] = d + 1
			queue = append(queue, Pos{current.r - 1, current.c})
		}
		
		// Check down
		if current.r+1 < H && grid[current.r+1][current.c] == '.' && dist[current.r+1][current.c] == -1 {
			dist[current.r+1][current.c] = d + 1
			queue = append(queue, Pos{current.r + 1, current.c})
		}
		
		// Check left
		if current.c-1 >= 0 && grid[current.r][current.c-1] == '.' && dist[current.r][current.c-1] == -1 {
			dist[current.r][current.c-1] = d + 1
			queue = append(queue, Pos{current.r, current.c - 1})
		}
		
		// Check right
		if current.c+1 < W && grid[current.r][current.c+1] == '.' && dist[current.r][current.c+1] == -1 {
			dist[current.r][current.c+1] = d + 1
			queue = append(queue, Pos{current.r, current.c + 1})
		}
	}
	
	fmt.Println(dist[tr][tc])
}

type Pos struct {
	r int
	c int
}