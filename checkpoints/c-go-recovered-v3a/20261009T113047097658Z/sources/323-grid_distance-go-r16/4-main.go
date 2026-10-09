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

	// Read all lines from stdin
	lines := make([]string, 0)
	buf, _ := reader.ReadString('\n')
	for strings.TrimSpace(buf) != "" {
		lines = append(lines, buf)
		buf, _ = reader.ReadString('\n')
	}

	if len(lines) == 0 {
		return
	}

	// Parse H W from first line
	firstLine := lines[0]
	parts := strings.Fields(firstLine)
	h, _ := strconv.Atoi(parts[0])
	w, _ := strconv.Atoi(parts[1])

	// Parse sr sc tr tc from second line
	secondLine := lines[1]
	parts = strings.Fields(secondLine)
	sr, _ := strconv.Atoi(parts[0])
	sc, _ := strconv.Atoi(parts[1])
	tr, _ := strconv.Atoi(parts[2])
	tc, _ := strconv.Atoi(parts[3])

	// Read grid (next H lines)
	grid := make([]string, h)
	for i := 0; i < h && len(lines) > 2+i; i++ {
		grid[i] = strings.TrimRight(lines[2+i], "\r\n")
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