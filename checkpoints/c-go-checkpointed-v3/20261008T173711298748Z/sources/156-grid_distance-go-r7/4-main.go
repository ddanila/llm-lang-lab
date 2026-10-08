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
	line1, _ := reader.ReadString('\n')
	fields := strings.Fields(line1)
	H, _ = strconv.Atoi(fields[0])
	W, _ = strconv.Atoi(fields[1])

	// Read sr sc tr tc
	line2, _ := reader.ReadString('\n')
	fields = strings.Fields(line2)
	sr, _ = strconv.Atoi(fields[0])
	sc, _ = strconv.Atoi(fields[1])
	tr, _ = strconv.Atoi(fields[2])
	tc, _ = strconv.Atoi(fields[3])

	// Read grid
	grid := make([]string, H)
	for i := 0; i < H; i++ {
		line, _ := reader.ReadString('\n')
		grid[i] = strings.TrimSpace(line)
	}

	// Check if start or end is blocked
	if sr >= H || sc >= W || tr >= H || tc >= W {
		fmt.Println("-1")
		return
	}
	if grid[sr][sc] == '#' || grid[tr][tc] == '#' {
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

	type pos struct {
		r, c int
	}
	queue := []pos{{sr, sc}}
	dist[sr][sc] = 0

	head := 0
	for head < len(queue) {
		curr := queue[head]
		head++
		d := dist[curr.r][curr.c]
		if curr.r == tr && curr.c == tc {
			fmt.Println(d)
			return
		}
		// Directions: up, down, left, right
		for _, dr := range []int{-1, 1, 0, 0} {
			for _, dc := range []int{0, 0, -1, 1} {
				nr, nc := curr.r+dr, curr.c+dc
				if nr >= 0 && nr < H && nc >= 0 && nc < W && grid[nr][nc] == '.' && dist[nr][nc] == -1 {
					dist[nr][nc] = d + 1
					queue = append(queue, pos{nr, nc})
				}
			}
		}
	}

	fmt.Println("-1")
}