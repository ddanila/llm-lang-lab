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

	// Validate start and end positions
	if sr < 0 || sr >= H || sc < 0 || sc >= W || tr < 0 || tr >= H || tc < 0 || tc >= W {
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

	queue := [][2]int{[sr, sc]}
	dist[sr][sc] = 0

	rowDx := []int{-1, 1, 0, 0}
	colDy := []int{0, 0, -1, 1}

	for len(queue) > 0 {
		curr := queue[0]
		queue = queue[1:]
		r, c := curr[0], curr[1]

		if r == tr && c == tc {
			break
		}

		currentDist := dist[r][c]

		for k := 0; k < 4; k++ {
			nr, nc := r+rowDx[k], c+colDy[k]
			if nr >= 0 && nr < H && nc >= 0 && nc < W && grid[nr][nc] == '.' && dist[nr][nc] == -1 {
				dist[nr][nc] = currentDist + 1
				queue = append(queue, [2]int{nr, nc})
			}
		}
	}

	fmt.Println(dist[tr][tc])
}