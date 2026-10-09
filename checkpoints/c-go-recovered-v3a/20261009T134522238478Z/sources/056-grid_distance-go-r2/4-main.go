package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	reader := bufio.NewReader(os.Stdin)

	var h, w int
	fmt.Fscanf(reader, "%d %d", &h, &w)

	sr, sc, tr, tc := 0, 0, 0, 0
	fmt.Fscanf(reader, "%d %d %d %d", &sr, &sc, &tr, &tc)

	grid := make([][]byte, h)
	for i := 0; i < h; i++ {
		line, _ := reader.ReadString('\n')
		line = line[:len(line)-1]
		if len(line) == 0 {
			continue
		}
		for j := 0; j < w && j < len(line); j++ {
			grid[i][j] = line[j]
		}
	}

	if grid[sr][sc] == '#' || grid[tr][tc] == '#' {
		fmt.Fprintln(os.Stdout, "-1")
		return
	}

	dist := make([][]int, h)
	for i := range dist {
		dist[i] = make([]int, w)
		for j := range dist[i] {
			dist[i][j] = -1
		}
	}

	q := [][2]int{}
	if grid[sr][sc] == '.' {
		q = append(q, [2]int{sr, sc})
		dist[sr][sc] = 0
	}

	dx := []int{-1, 1, 0, 0}
	dy := []int{0, 0, -1, 1}

	head := 0
	for head < len(q) {
		x, y := q[head][0], q[head][1]
		head++
		d := dist[x][y]

		for k := 0; k < 4; k++ {
			nx, ny := x+dx[k], y+dy[k]
			if nx >= 0 && nx < h && ny >= 0 && ny < w && grid[nx][ny] == '.' && dist[nx][ny] == -1 {
				dist[nx][ny] = d + 1
				q = append(q, [2]int{nx, ny})
			}
		}
	}

	if dist[tr][tc] == -1 {
		fmt.Fprintln(os.Stdout, "-1")
	} else {
		fmt.Fprintln(os.Stdout, dist[tr][tc])
	}
}