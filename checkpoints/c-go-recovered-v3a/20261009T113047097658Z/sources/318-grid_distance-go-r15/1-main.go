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

	// Read H W sr sc tr tc
	line, _ := reader.ReadString('\n')
	tokens := strings.Fields(line)
	if len(tokens) < 6 {
		return
	}
	H, _ := strconv.Atoi(tokens[0])
	W, _ := strconv.Atoi(tokens[1])
	sr, _ := strconv.Atoi(tokens[2])
	sc, _ := strconv.Atoi(tokens[3])
	tr, _ := strconv.Atoi(tokens[4])
	tc, _ := strconv.Atoi(tokens[5])

	// Read grid
	grid := make([]string, H)
	for i := 0; i < H; i++ {
		line, _ := reader.ReadString('\n')
		grid[i] = strings.TrimRight(line, "\r\n")
	}

	// Validate start and end
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

	queue := [][2]int{[2]int{sr, sc}}
	dist[sr][sc] = 0

	dr := []int{-1, 1, 0, 0}
	dc := []int{0, 0, -1, 1}

	for len(queue) > 0 {
		current := queue[0]
		queue = queue[1:]

		r, c := current[0], current[1]
		if r == tr && c == tc {
			fmt.Println(dist[r][c])
			return
		}

		for k := 0; k < 4; k++ {
			nr, nc := r+dr[k], c+dc[k]
			if nr >= 0 && nr < H && nc >= 0 && nc < W && grid[nr][nc] == '.' && dist[nr][nc] == -1 {
				dist[nr][nc] = dist[r][c] + 1
				queue = append(queue, [2]int{nr, nc})
			}
		}
	}

	fmt.Println("-1")
}