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

	// Read sr, sc, tr, tc
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
		// Remove trailing newline but preserve the row content
		line = strings.TrimRight(line, "\n\r")
		// Pad with '.' if line is shorter than W
		for len(line) < W {
			line += "."
		}
		grid[i] = line[:W] // Take exactly W characters
	}

	// Check if start or target is blocked or out of bounds
	if sr < 0 || sr >= H || sc < 0 || sc >= W || tr < 0 || tr >= H || tc < 0 || tc >= W {
		fmt.Println("-1")
		return
	}

	if grid[sr][sc] == '#' || grid[tr][tc] == '#' {
		fmt.Println("-1")
		return
	}

	// BFS
	queue := make([][]int, 0)
	queue = append(queue, []int{sr, sc})
	dist := make([][]int, H)
	for i := range dist {
		dist[i] = make([]int, W)
		for j := range dist[i] {
			dist[i][j] = -1
		}
	}
	dist[sr][sc] = 0

	dx := []int{-1, 1, 0, 0}
	dy := []int{0, 0, -1, 1}

	for len(queue) > 0 {
		curr := queue[0]
		queue = queue[1:]
		x, y := curr[0], curr[1]

		if x == tr && y == tc {
			fmt.Println(dist[x][y])
			return
		}

		for i := 0; i < 4; i++ {
			nx, ny := x+dx[i], y+dy[i]
			if nx >= 0 && nx < H && ny >= 0 && ny < W && grid[nx][ny] == '.' && dist[nx][ny] == -1 {
				dist[nx][ny] = dist[x][y] + 1
				queue = append(queue, []int{nx, ny})
			}
		}
	}

	fmt.Println("-1")
}