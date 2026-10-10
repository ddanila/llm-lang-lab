package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	reader := bufio.NewReader(os.Stdin)

	// Read H W
	line, err := reader.ReadString('\n')
	if err != nil {
		return
	}
	line = strings.TrimSpace(line)
	parts := strings.Fields(line)
	H, _ := strconv.Atoi(parts[0])
	W, _ := strconv.Atoi(parts[1])

	// Read sr sc tr tc - might be on same line or next line
	line2, err := reader.ReadString('\n')
	if err != nil {
		return
	}
	
	// Handle case where there might not be a second line (EOF after grid)
	if len(line2) == 1 && line2[0] == '\n' {
		// No more input, treat as empty tokens
		fmt.Println("-1")
		return
	}
	
	tokens := strings.Fields(strings.TrimSpace(line2))
	sr, _ := strconv.Atoi(tokens[0])
	sc, _ := strconv.Atoi(tokens[1])
	tr, _ := strconv.Atoi(tokens[2])
	tc, _ := strconv.Atoi(tokens[3])

	// Read grid
	grid := make([]string, H)
	for i := 0; i < H; i++ {
		line, err := reader.ReadString('\n')
		if err != nil {
			return
		}
		grid[i] = strings.TrimSpace(line)
	}

	// Validate start and end points
	if sr < 0 || sr >= H || sc < 0 || sc >= W || len(grid[sr]) <= sc || grid[sr][sc] == '#' {
		fmt.Println("-1")
		return
	}
	if tr < 0 || tr >= H || tc < 0 || tc >= W || len(grid[tr]) <= tc || grid[tr][tc] == '#' {
		fmt.Println("-1")
		return
	}

	// BFS for shortest path
	dist := make([][]int, H)
	for i := range dist {
		dist[i] = make([]int, W)
		for j := range dist[i] {
			dist[i][j] = -1
		}
	}

	queue := [][2]int{}
	queue = append(queue, [2]int{sr, sc})
	dist[sr][sc] = 0

	head := 0
	for head < len(queue) {
		r, c := queue[head][0], queue[head][1]
		head++
		d := dist[r][c]

		if r == tr && c == tc {
			fmt.Println(d)
			return
		}

		// Directions: up, down, left, right
		dr := []int{-1, 1, 0, 0}
		dc := []int{0, 0, -1, 1}

		for k := 0; k < 4; k++ {
			nr, nc := r+dr[k], c+dc[k]
			if nr >= 0 && nr < H && nc >= 0 && nc < W && len(grid[nr]) > nc && grid[nr][nc] == '.' && dist[nr][nc] == -1 {
				dist[nr][nc] = d + 1
				queue = append(queue, [2]int{nr, nc})
			}
		}
	}

	fmt.Println("-1")
}