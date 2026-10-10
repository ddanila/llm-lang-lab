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
	line1, err := reader.ReadString('\n')
	if err != nil {
		return
	}
	line1 = strings.TrimSpace(line1)
	parts := strings.Split(line1, " ")
	H, _ := strconv.Atoi(parts[0])
	W, _ := strconv.Atoi(parts[1])

	// Read sr, sc, tr, tc
	line2, err := reader.ReadString('\n')
	if err != nil {
		return
	}
	line2 = strings.TrimSpace(line2)
	parts = strings.Split(line2, " ")
	sr, _ := strconv.Atoi(parts[0])
	sc, _ := strconv.Atoi(parts[1])
	tr, _ := strconv.Atoi(parts[2])
	tc, _ := strconv.Atoi(parts[3])

	// Read grid
	grid := make([]string, H)
	for i := 0; i < H; i++ {
		line, err := reader.ReadString('\n')
		if err != nil {
			return
		}
		grid[i] = strings.TrimSpace(line)
	}

	// Check if start or end is blocked
	if grid[sr][sc] == '#' || grid[tr][tc] == '#' {
		fmt.Println("-1")
		return
	}

	// BFS
	queue := make([]int, 0)
	dist := make([][]int, H)
	for i := range dist {
		dist[i] = make([]int, W)
		for j := range dist[i] {
			dist[i][j] = -1
		}
	}

	queue = append(queue, sr*W+sc)
	dist[sr][sc] = 0

	row := 0
	col := 0
	dr := []int{-1, 0, 0, 1}
	dc := []int{0, -1, 1, 0}

	for len(queue) > 0 {
		pos := queue[0]
		queue = queue[1:]
		r := pos / W
		c := pos % W

		if r == tr && c == tc {
			fmt.Println(dist[r][c])
			return
		}

		for k := 0; k < 4; k++ {
			nr, nc := r+dr[k], c+dc[k]
			if nr >= 0 && nr < H && nc >= 0 && nc < W && grid[nr][nc] == '.' && dist[nr][nc] == -1 {
				dist[nr][nc] = dist[r][c] + 1
				queue = append(queue, nr*W+nc)
			}
		}
	}

	fmt.Println("-1")
}