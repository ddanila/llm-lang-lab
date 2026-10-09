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

	// Read H and W
	hStr, _ := reader.ReadString('\n')
	hStr = strings.TrimSpace(hStr)
	h, _ := strconv.Atoi(hStr)

	wStr, _ := reader.ReadString('\n')
	wStr = strings.TrimSpace(wStr)
	w, _ := strconv.Atoi(wStr)

	srStr, _ := reader.ReadString('\n')
	srStr = strings.TrimSpace(srStr)
	sr, _ := strconv.Atoi(srStr)

	scStr, _ := reader.ReadString('\n')
	scStr = strings.TrimSpace(scStr)
	sc, _ := strconv.Atoi(scStr)

	trStr, _ := reader.ReadString('\n')
	trStr = strings.TrimSpace(trStr)
	tr, _ := strconv.Atoi(trStr)

	tcStr, _ := reader.ReadString('\n')
	tcStr = strings.TrimSpace(tcStr)
	tc, _ := strconv.Atoi(tcStr)

	// Read grid rows
	grid := make([]string, h)
	for i := 0; i < h; i++ {
		line, _ := reader.ReadString('\n')
		line = strings.TrimSpace(line)
		if len(line) > w {
			line = line[:w]
		}
		grid[i] = line
	}

	// Validate start and end points
	if grid[sr][sc] == '#' || grid[tr][tc] == '#' {
		fmt.Println("-1")
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

	queue := []struct{ r, c int }{{sr, sc}}
	dist[sr][sc] = 0

	dr := []int{-1, 1, 0, 0}
	dc := []int{0, 0, -1, 1}

	for len(queue) > 0 {
		curr := queue[0]
		queue = queue[1:]

		if curr.r == tr && curr.c == tc {
			break
		}

		for k := 0; k < 4; k++ {
			nr, nc := curr.r+dr[k], curr.c+dc[k]
			if nr >= 0 && nr < h && nc >= 0 && nc < w && grid[nr][nc] != '#' && dist[nr][nc] == -1 {
				dist[nr][nc] = dist[curr.r][curr.c] + 1
				queue = append(queue, struct{ r, c int }{nr, nc})
			}
		}
	}

	fmt.Println(dist[tr][tc])
}