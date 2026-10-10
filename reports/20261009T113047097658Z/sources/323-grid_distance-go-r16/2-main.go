package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

func main() {
	reader := bufio.NewReader(os.Stdin)

	// Read all input lines
	lines := make([]string, 0)
	for {
		line, err := reader.ReadString('\n')
		if err != nil {
			break
		}
		lines = append(lines, line)
	}

	// Parse H W from first line
	firstLine := trim(lines[0])
	parts := split(firstLine)
	h, _ := strconv.Atoi(parts[0])
	w, _ := strconv.Atoi(parts[1])

	// Parse sr sc tr tc from second line
	secondLine := trim(lines[1])
	parts = split(secondLine)
	sr, _ := strconv.Atoi(parts[0])
	sc, _ := strconv.Atoi(parts[1])
	tr, _ := strconv.Atoi(parts[2])
	tc, _ := strconv.Atoi(parts[3])

	// Read grid (next H lines)
	grid := make([]string, h)
	for i := 0; i < h; i++ {
		if len(lines) > 2+i {
			grid[i] = trim(lines[2+i])
		} else {
			grid[i] = ""
		}
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
	for end > start && (s[end-1] == '\n' || s[end-1] == '\r' || s[end-1] == ' ') {
		end--
	}
	return s[start:end]
}

func split(s string) []string {
	var parts []string
	start := 0
	for i := 0; i < len(s); i++ {
		if s[i] == ' ' || s[i] == '\t' {
			if i > start {
				parts = append(parts, s[start:i])
				start = i + 1
			}
		}
	}
	if start < len(s) {
		parts = append(parts, s[start:len(s)])
	}
	return parts
}