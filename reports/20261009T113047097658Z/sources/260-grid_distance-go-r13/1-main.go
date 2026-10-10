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
	fields := strings.Fields(line)
	H, _ := strconv.Atoi(fields[0])
	W, _ := strconv.Atoi(fields[1])

	// Read sr sc tr tc
	line2, _ := reader.ReadString('\n')
	fields2 := strings.Fields(line2)
	sr, _ := strconv.Atoi(fields2[0])
	sc, _ := strconv.Atoi(fields2[1])
	tr, _ := strconv.Atoi(fields2[2])
	tc, _ := strconv.Atoi(fields2[3])

	// Read grid
	grid := make([]string, H)
	for i := 0; i < H; i++ {
		line, _ := reader.ReadString('\n')
		grid[i] = strings.TrimRight(line, "\n")
	}

	// Check if start or target is blocked
	if sr < 0 || sr >= H || sc < 0 || sc >= W || grid[sr][sc] == '#' {
		fmt.Println("-1")
		return
	}
	if tr < 0 || tr >= H || tc < 0 || tc >= W || grid[tr][tc] == '#' {
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