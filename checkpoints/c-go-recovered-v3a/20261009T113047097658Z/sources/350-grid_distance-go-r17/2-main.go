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
	line = strings.TrimSpace(line)
	parts := strings.Fields(line)
	H, _ := strconv.Atoi(parts[0])
	W, _ := strconv.Atoi(parts[1])

	// Read sr, sc, tr, tc
	line2, _ := reader.ReadString('\n')
	line2 = strings.TrimSpace(line2)
	tokens := strings.Fields(line2)
	sr, _ := strconv.Atoi(tokens[0])
	sc, _ := strconv.Atoi(tokens[1])
	tr, _ := strconv.Atoi(tokens[2])
	tc, _ := strconv.Atoi(tokens[3])

	// Read grid
	grid := make([]string, H)
	for i := 0; i < H; i++ {
		line3, _ := reader.ReadString('\n')
		grid[i] = strings.TrimSpace(line3)
	}

	// Check if endpoints are blocked
	if grid[sr][sc] == '#' || grid[tr][tc] == '#' {
		fmt.Println("-1")
		return
	}

	// BFS
	queue := make([][]int, 0)
	dist := make([][]int, H)
	for i := range dist {
		dist[i] = make([]int, W)
		for j := range dist[i] {
			dist[i][j] = -1
		}
	}

	queue = append(queue, []int{sr, sc})
	dist[sr][sc] = 0

	rows := []int{-1, 1, 0, 0}
	cols := []int{0, 0, -1, 1}

	for len(queue) > 0 {
		curr := queue[0]
		queue = queue[1:]
		r, c := curr[0], curr[1]
		d := dist[r][c]

		if r == tr && c == tc {
			fmt.Println(d)
			return
		}

		for k := 0; k < 4; k++ {
			nr, nc := r+rows[k], c+cols[k]
			if nr >= 0 && nr < H && nc >= 0 && nc < W && grid[nr][nc] == '.' && dist[nr][nc] == -1 {
				dist[nr][nc] = d + 1
				queue = append(queue, []int{nr, nc})
			}
		}
	}

	fmt.Println("-1")
}