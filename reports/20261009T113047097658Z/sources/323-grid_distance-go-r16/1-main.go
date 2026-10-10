package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

func main() {
	reader := bufio.NewReader(os.Stdin)

	// Read H and W
	hStr, _ := reader.ReadString('\n')
	hStr = trim(hStr)
	h, err := strconv.Atoi(hStr)
	if err != nil {
		return
	}

	wStr, _ := reader.ReadString('\n')
	wStr = trim(wStr)
	w, err := strconv.Atoi(wStr)
	if err != nil {
		return
	}

	srStr, _ := reader.ReadString('\n')
	srStr = trim(srStr)
	sr, err := strconv.Atoi(srStr)
	if err != nil {
		return
	}

	scStr, _ := reader.ReadString('\n')
	scStr = trim(scStr)
	sc, err := strconv.Atoi(scStr)
	if err != nil {
		return
	}

	trStr, _ := reader.ReadString('\n')
	trStr = trim(trStr)
	tr, err := strconv.Atoi(trStr)
	if err != nil {
		return
	}

	tcStr, _ := reader.ReadString('\n')
	tcStr = trim(tcStr)
	tc, err := strconv.Atoi(tcStr)
	if err != nil {
		return
	}

	// Read grid
	grid := make([]string, h)
	for i := 0; i < h; i++ {
		line, _ := reader.ReadString('\n')
		grid[i] = trim(line)
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

func trim(s string) string {
	start := 0
	end := len(s)
	for start < end && s[start] == ' ' {
		start++
	}
	for end > start && s[end-1] == '\n' || s[end-1] == '\r' || s[end-1] == ' ' {
		end--
	}
	return s[start:end]
}