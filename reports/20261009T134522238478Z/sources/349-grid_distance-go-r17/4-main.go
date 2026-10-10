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

	// Read all input
	input, _ := reader.ReadString('\n')
	fields := strings.Fields(input)
	if len(fields) < 2 {
		return
	}
	H, _ = strconv.Atoi(fields[0])
	W, _ = strconv.Atoi(fields[1])

	// Read second line for sr sc tr tc
	input2, _ := reader.ReadString('\n')
	fields = strings.Fields(input2)
	if len(fields) < 4 {
		return
	}
	sr, _ = strconv.Atoi(fields[0])
	sc, _ = strconv.Atoi(fields[1])
	tr, _ = strconv.Atoi(fields[2])
	tc, _ = strconv.Atoi(fields[3])

	// Read grid lines
	grid := make([][]byte, H)
	for i := 0; i < H; i++ {
		line, _ := reader.ReadString('\n')
		line = strings.TrimRight(line, "\r\n")
		if len(line) == 0 {
			continue
		}
		// Pad with '.' if line is shorter than W
		grid[i] = make([]byte, W)
		for j := 0; j < len(line) && j < W; j++ {
			grid[i][j] = line[j]
		}
		for j := len(line); j < W; j++ {
			grid[i][j] = '.'
		}
	}

	// Check if start or target is blocked
	if sr >= H || sc >= W || tr >= H || tc >= W {
		fmt.Println("-1")
		return
	}
	if grid[sr][sc] == '#' || grid[tr][tc] == '#' {
		fmt.Println("-1")
		return
	}

	// BFS for shortest path
	queue := [][2]int{[2]int{sr, sc}}
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

	found := false
	for len(queue) > 0 {
		curr := queue[0]
		queue = queue[1:]

		x, y := curr[0], curr[1]

		if x == tr && y == tc {
			found = true
			break
		}

		for i := 0; i < 4; i++ {
			nx, ny := x+dx[i], y+dy[i]
			if nx >= 0 && nx < H && ny >= 0 && ny < W && grid[nx][ny] == '.' && dist[nx][ny] == -1 {
				dist[nx][ny] = dist[x][y] + 1
				queue = append(queue, [2]int{nx, ny})
			}
		}
	}

	if found {
		fmt.Println(dist[tr][tc])
	} else {
		fmt.Println("-1")
	}
}