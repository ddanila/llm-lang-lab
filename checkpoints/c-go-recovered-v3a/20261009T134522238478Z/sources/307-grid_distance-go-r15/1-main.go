package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func main() {
	reader := bufio.NewReader(os.Stdin)

	// Read H W sr sc tr tc
	line, _ := reader.ReadString('\n')
	fields := strings.Fields(line)
	if len(fields) < 6 {
		return
	}
	H, W, sr, sc, tr, tc := parseInts(fields[0], fields[1], fields[2], fields[3], fields[4], fields[5])

	// Read grid
	grid := make([]string, H)
	for i := 0; i < H; i++ {
		line, _ = reader.ReadString('\n')
		grid[i] = strings.TrimRight(line, "\n")
	}

	// Check if start or end is blocked
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

	q := [][2]int{}
	dr := []int{-1, 1, 0, 0}
	dc := []int{0, 0, -1, 1}

	q = append(q, [2]int{sr, sc})
	dist[sr][sc] = 0

	head := 0
	for head < len(q) {
		curr := q[head]
	head++
		r, c := curr[0], curr[1]
		d := dist[r][c]

		if r == tr && c == tc {
			fmt.Println(d)
			return
		}

		for i := 0; i < 4; i++ {
			nr, nc := r+dr[i], c+dc[i]
			if nr >= 0 && nr < H && nc >= 0 && nc < W && grid[nr][nc] == '.' && dist[nr][nc] == -1 {
				dist[nr][nc] = d + 1
				q = append(q, [2]int{nr, nc})
			}
		}
	}

	fmt.Println("-1")
}

func parseInts(s ...string) []int {
	result := make([]int, len(s))
	for i, s := range s {
		result[i] = 0
		if v, err := fmt.Sscanf(s, "%d", &result[i]); err != nil || v == 0 {
			return result
		}
	}
	return result
}