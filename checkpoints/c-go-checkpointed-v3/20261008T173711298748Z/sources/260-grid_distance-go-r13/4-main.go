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

	// Read H W from first line
	line, err := reader.ReadString('\n')
	if err != nil || len(line) == 0 {
		return
	}
	fields := strings.Fields(line)
	if len(fields) < 2 {
		return
	}
	H, _ := strconv.Atoi(fields[0])
	W, _ := strconv.Atoi(fields[1])

	// Read sr sc tr tc from second line
	line, err = reader.ReadString('\n')
	if err != nil || len(line) == 0 {
		return
	}
	fields = strings.Fields(line)
	if len(fields) < 4 {
		return
	}
	sr, _ := strconv.Atoi(fields[0])
	sc, _ := strconv.Atoi(fields[1])
	tr, _ := strconv.Atoi(fields[2])
	tc, _ := strconv.Atoi(fields[3])

	// Read grid rows
	grid := make([]string, H)
	for i := 0; i < H; i++ {
		line, err := reader.ReadString('\n')
		if err != nil || len(line) == 0 {
			break
		}
		// Keep only the first W characters (or all if less than W)
		grid[i] = line[:min(len(line), W)]
	}

	// Check if start or target is blocked or out of bounds
	if sr < 0 || sr >= H || sc < 0 || sc >= W {
		fmt.Println("-1")
		return
	}
	if tr < 0 || tr >= H || tc < 0 || tc >= W {
		fmt.Println("-1")
		return
	}
	if grid[sr][sc] == '#' {
		fmt.Println("-1")
		return
	}
	if grid[tr][tc] == '#' {
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

	queue := [][2]int{}
	queue = append(queue, [2]int{sr, sc})
	dist[sr][sc] = 0

	dx := []int{-1, 1, 0, 0}
	dy := []int{0, 0, -1, 1}

	for len(queue) > 0 {
		current := queue[0]
		queue = queue[1:]

		x, y := current[0], current[1]

		if x == tr && y == tc {
			fmt.Println(dist[x][y])
			return
		}

		for k := 0; k < 4; k++ {
			nx, ny := x+dx[k], y+dy[k]
			if nx >= 0 && nx < H && ny >= 0 && ny < W && grid[nx][ny] != '#' && dist[nx][ny] == -1 {
				dist[nx][ny] = dist[x][y] + 1
				queue = append(queue, [2]int{nx, ny})
			}
		}
	}

	fmt.Println("-1")
}

func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}