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

	// Read all tokens from stdin
	tokens := []string{}
	buf, _ := reader.ReadString('\n')
	for strings.TrimSpace(buf) != "" {
		for _, t := range strings.Fields(buf) {
			tokens = append(tokens, t)
		}
		buf, _ = reader.ReadString('\n')
	}

	if len(tokens) < 8 {
		return
	}

	h, _ := strconv.Atoi(tokens[0])
	w, _ := strconv.Atoi(tokens[1])
	sr, _ := strconv.Atoi(tokens[2])
	sc, _ := strconv.Atoi(tokens[3])
	tr, _ := strconv.Atoi(tokens[4])
	tc, _ := strconv.Atoi(tokens[5])

	// Read grid lines - each line is a token if it's on its own line
	// But we need to read exactly H rows
	grid := make([]string, h)
	idx := 6
	for i := 0; i < h && idx < len(tokens); i++ {
		grid[i] = tokens[idx]
		idx++
	}

	// Check if start or end is blocked
	if sr < 0 || sr >= h || sc < 0 || sc >= w || grid[sr][sc] == '#' {
		fmt.Println("-1")
		return
	}
	if tr < 0 || tr >= h || tc < 0 || tc >= w || grid[tr][tc] == '#' {
		fmt.Println("-1")
		return
	}

	// If start equals end
	if sr == tr && sc == tc {
		fmt.Println("0")
		return
	}

	// BFS
	dist := make([][]int, h)
	for i := range dist {
		dist[i] = make([]int, w)
		for j := range dist[i] {
			dist[i][j] = -1
		}
	}

	queue := [][2]int{}
	queue = append(queue, [2]int{sr, sc})
	dist[sr][sc] = 0

	dr := []int{-1, 1, 0, 0}
	dc := []int{0, 0, -1, 1}

	head := 0
	for head < len(queue) {
		curr := queue[head]
		head++
		r, c := curr[0], curr[1]
		d := dist[r][c]

		for i := 0; i < 4; i++ {
			nr, nc := r+dr[i], c+dc[i]
			if nr >= 0 && nr < h && nc >= 0 && nc < w && grid[nr][nc] != '#' && dist[nr][nc] == -1 {
				dist[nr][nc] = d + 1
				queue = append(queue, [2]int{nr, nc})
			}
		}
	}

	fmt.Println(dist[tr][tc])
}