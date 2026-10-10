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

	// Read H and W
	line, err := reader.ReadString('\n')
	if err != nil {
		return
	}
	fields := strings.Fields(line)
	if len(fields) < 2 {
		return
	}
	H, _ := strconv.Atoi(fields[0])
	W, _ := strconv.Atoi(fields[1])

	// Read start and target coordinates
	line, err = reader.ReadString('\n')
	if err != nil {
		return
	}
	fields = strings.Fields(line)
	sr, _ := strconv.Atoi(fields[0])
	sc, _ := strconv.Atoi(fields[1])
	tr, _ := strconv.Atoi(fields[2])
	tc, _ := strconv.Atoi(fields[3])

	// Read grid
	grid := make([]string, H)
	for i := 0; i < H; i++ {
		line, err = reader.ReadString('\n')
		if err != nil {
			return
		}
		grid[i] = strings.TrimRight(line, "\n")
	}

	// Validate start and target are within bounds
	if sr < 0 || sr >= H || sc < 0 || sc >= W || tr < 0 || tr >= H || tc < 0 || tc >= W {
		fmt.Println("-1")
		return
	}

	// Check if start or target is blocked
	if grid[sr][sc] == '#' || grid[tr][tc] == '#' {
		fmt.Println("-1")
		return
	}

	// BFS to find shortest path
	queue := [][2]int{{sr, sc}}
	dist := make([][]int, H)
	for i := range dist {
		dist[i] = make([]int, W)
		for j := range dist[i] {
			dist[i][j] = -1
		}
	}
	dist[sr][sc] = 0

	dr := []int{-1, 1, 0, 0}
	dc := []int{0, 0, -1, 1}

	for len(queue) > 0 {
		curr := queue[0]
		queue = queue[1:]
		r, c := curr[0], curr[1]

		if r == tr && c == tc {
			break
		}

		for k := 0; k < 4; k++ {
			nr, nc := r+dr[k], c+dc[k]
			if nr >= 0 && nr < H && nc >= 0 && nc < W && grid[nr][nc] == '.' && dist[nr][nc] == -1 {
				dist[nr][nc] = dist[r][c] + 1
				queue = append(queue, [2]int{nr, nc})
			}
		}
	}

	fmt.Println(dist[tr][tc])
}