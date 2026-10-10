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
	H, W, sr, sc, tr, tc := 0, 0, 0, 0, 0, 0
	fmt.Sscanf(fields[0], "%d", &H)
	fmt.Sscanf(fields[1], "%d", &W)
	fmt.Sscanf(fields[2], "%d", &sr)
	fmt.Sscanf(fields[3], "%d", &sc)
	fmt.Sscanf(fields[4], "%d", &tr)
	fmt.Sscanf(fields[5], "%d", &tc)

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