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
	fields := strings.Fields(line1)
	H, _ := strconv.Atoi(fields[0])
	W, _ := strconv.Atoi(fields[1])

	// Read sr, sc, tr, tc
	line2, err := reader.ReadString('\n')
	if err != nil {
		return
	}
	fields = strings.Fields(line2)
	sr, _ := strconv.Atoi(fields[0])
	sc, _ := strconv.Atoi(fields[1])
	tr, _ := strconv.Atoi(fields[2])
	tc, _ := strconv.Atoi(fields[3])

	// Read grid - handle lines that might be shorter than W
	grid := make([][]byte, H)
	for i := 0; i < H; i++ {
		line, _ := reader.ReadString('\n')
		line = strings.TrimRight(line, "\r\n")
		if len(line) == 0 {
			continue
		}
		grid[i] = []byte(line)
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