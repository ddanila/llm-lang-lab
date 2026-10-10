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
	line0 := strings.TrimSpace(scanner.Text())
	parts := strings.Fields(line0)
	if len(parts) < 6 {
		return
	}
	H, _ := strconv.Atoi(parts[0])
	W, _ := strconv.Atoi(parts[1])
	sr, _ := strconv.Atoi(parts[2])
	sc, _ := strconv.Atoi(parts[3])
	tr, _ := strconv.Atoi(parts[4])
	tc, _ := strconv.Atoi(parts[5])

	grid := make([]string, H)
	if !scanner.Scan() {
		return
	}
	for i := 0; i < H; i++ {
		grid[i] = scanner.Text()
	}

	startBlocked := grid[sr][sc] == '#'
	endBlocked := grid[tr][tc] == '#'

	if startBlocked || endBlocked {
		fmt.Println("-1")
		return
	}

	if sr == tr && sc == tc {
		fmt.Println("0")
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

	queue := [][2]int{}
	dist[sr][sc] = 0
	queue = append(queue, [2]int{sr, sc})
	head := 0

	dr := []int{-1, 1, 0, 0}
	dc := []int{0, 0, -1, 1}

	for head < len(queue) {
		r, c := queue[head]
		head++
		currDist := dist[r][c]

		if r == tr && c == tc {
			fmt.Println(currDist)
			return
		}

		for k := 0; k < 4; k++ {
			nr, nc := r+dr[k], c+dc[k]
			if nr >= 0 && nr < H && nc >= 0 && nc < W && grid[nr][nc] == '.' && dist[nr][nc] == -1 {
				dist[nr][nc] = currDist + 1
				queue = append(queue, [2]int{nr, nc})
			}
		}
	}

	fmt.Println("-1")
}