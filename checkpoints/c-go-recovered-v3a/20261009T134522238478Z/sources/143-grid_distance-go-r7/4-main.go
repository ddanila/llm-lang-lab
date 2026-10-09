package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

func main() {
	reader := bufio.NewReader(os.Stdin)

	// Read H and W from first line
	line, _ := reader.ReadString('\n')
	line = trim(line)
	parts := split(line)
	if len(parts) < 2 {
		fmt.Fprintln(os.Stderr, "Error reading H")
		return
	}
	h, err := strconv.Atoi(parts[0])
	if err != nil {
		fmt.Fprintln(os.Stderr, "Error reading H")
		return
	}
	w, err := strconv.Atoi(parts[1])
	if err != nil {
		fmt.Fprintln(os.Stderr, "Error reading W")
		return
	}

	// Read sr, sc, tr, tc from next lines
	srStr, _ := reader.ReadString('\n')
	srStr = trim(srStr)
	scStr, _ := reader.ReadString('\n')
	scStr = trim(scStr)
	trStr, _ := reader.ReadString('\n')
	trStr = trim(trStr)
	tcStr, _ := reader.ReadString('\n')
	tcStr = trim(tcStr)

	sr, err = strconv.Atoi(srStr)
	if err != nil {
		fmt.Fprintln(os.Stderr, "Error reading sr")
		return
	}
	sc, err = strconv.Atoi(scStr)
	if err != nil {
		fmt.Fprintln(os.Stderr, "Error reading sc")
		return
	}
	tr, err = strconv.Atoi(trStr)
	if err != nil {
		fmt.Fprintln(os.Stderr, "Error reading tr")
		return
	}
	tc, err = strconv.Atoi(tcStr)
	if err != nil {
		fmt.Fprintln(os.Stderr, "Error reading tc")
		return
	}

	// Read grid rows
	grid := make([]string, h)
	for i := 0; i < h; i++ {
		line, _ = reader.ReadString('\n')
		grid[i] = trim(line)
	}

	// Check if start or target is blocked or out of bounds
	if sr < 0 || sr >= h || sc < 0 || sc >= w || grid[sr][sc] == '#' {
		fmt.Println("-1")
		return
	}
	if tr < 0 || tr >= h || tc < 0 || tc >= w || grid[tr][tc] == '#' {
		fmt.Println("-1")
		return
	}

	// BFS to find shortest path
	queue := [][2]int{{sr, sc}}
	dist := make([][]int, h)
	for i := range dist {
		dist[i] = make([]int, w)
		for j := range dist[i] {
			dist[i][j] = -1
		}
	}

	dist[sr][sc] = 0
	dr := []int{-1, 1, 0, 0}
	dc := []int{0, 0, -1, 1}

	for len(queue) > 0 {
		curr := queue[0]
		queue = queue[1:]

		r, c := curr[0], curr[1]

		if r == tr && c == tc {
			fmt.Println(dist[r][c])
			return
		}

		for k := 0; k < 4; k++ {
			nr, nc := r+dr[k], c+dc[k]
			if nr >= 0 && nr < h && nc >= 0 && nc < w && grid[nr][nc] == '.' && dist[nr][nc] == -1 {
				dist[nr][nc] = dist[r][c] + 1
				queue = append(queue, [2]int{nr, nc})
			}
		}
	}

	// If target is unreachable
	fmt.Println("-1")
}

func trim(s string) string {
	start := 0
	end := len(s)
	for start < end && (s[start] == ' ' || s[start] == '\t') {
		start++
	}
	for end > start && (s[end-1] == ' ' || s[end-1] == '\t' || s[end-1] == '\n' || s[end-1] == '\r') {
		end--
	}
	return s[start:end]
}

func split(s string) []string {
	var parts []string
	start := 0
	for i := 0; i <= len(s); i++ {
		if i == len(s) || s[i] == ' ' || s[i] == '\t' || s[i] == '\n' || s[i] == '\r' {
			if i > start {
				parts = append(parts, s[start:i])
			}
			start = i + 1
		}
	}
	return parts
}