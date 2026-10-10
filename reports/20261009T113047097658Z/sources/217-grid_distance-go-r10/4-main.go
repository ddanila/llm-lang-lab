package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	if !scanner.Scan() {
		return
	}
	line1 := scanner.Text()
	fields := strings.Fields(line1)
	if len(fields) < 6 {
		return
	}
	H, _ := strconv.Atoi(fields[0])
	W, _ := strconv.Atoi(fields[1])
	sr, _ := strconv.Atoi(fields[2])
	sc, _ := strconv.Atoi(fields[3])
	tr, _ := strconv.Atoi(fields[4])
	tc, _ := strconv.Atoi(fields[5])

	if !scanner.Scan() {
		return
	}
	grid := make([]string, H)
	for i := 0; i < H; i++ {
		if !scanner.Scan() {
			break
		}
		grid[i] = scanner.Text()
	}

	// Validate start and end coordinates
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
	for i := range dist {
		dist[i] = make([]int, W)
		for j := range dist[i] {
			dist[i][j] = -1
		}
	}

	queue := []struct{ r, c int }{{sr, sc}}
	dist[sr][sc] = 0

	rDelta := []int{-1, 1, 0, 0}
	cDelta := []int{0, 0, -1, 1}

	for len(queue) > 0 {
		curr := queue[0]
		queue = queue[1:]

		if curr.r == tr && curr.c == tc {
			break
		}

		currentDist := dist[curr.r][curr.c]

		for k := 0; k < 4; k++ {
			nr, nc := curr.r+rDelta[k], curr.c+cDelta[k]
			if nr >= 0 && nr < H && nc >= 0 && nc < W && grid[nr][nc] == '.' && dist[nr][nc] == -1 {
				dist[nr][nc] = currentDist + 1
				queue = append(queue, struct{ r, c int }{nr, nc})
			}
		}
	}

	fmt.Println(dist[tr][tc])
}