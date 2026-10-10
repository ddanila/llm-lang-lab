package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	if !scanner.Scan() {
		return
	}
	parts := split(scanner.Text())
	if len(parts) < 6 {
		return
	}
	H, _ := strconv.Atoi(parts[0])
	W, _ := strconv.Atoi(parts[1])
	sr, _ := strconv.Atoi(parts[2])
	sc, _ := strconv.Atoi(parts[3])
	tr, _ := strconv.Atoi(parts[4])
	tc, _ := strconv.Atoi(parts[5])

	grid := make([]string, H)
	for i := 0; i < H; i++ {
		if !scanner.Scan() {
			break
		}
		grid[i] = scanner.Text()
	}

	if sr < 0 || sr >= H || sc < 0 || sc >= W || tr < 0 || tr >= H || tc < 0 || tc >= W {
		fmt.Println("-1")
		return
	}
	if grid[sr][sc] == '#' || grid[tr][tc] == '#' {
		fmt.Println("-1")
		return
	}

	dist := make([][]int, H)
	for i := range dist {
		dist[i] = make([]int, W)
	}
	for i := 0; i < H; i++ {
		for j := 0; j < W; j++ {
			if grid[i][j] == '.' {
				dist[i][j] = -1
			} else {
				dist[i][j] = 1000000
			}
		}
	}

	queue := make([][]int, H)
	for i := range queue {
		queue[i] = []int{}
	}
	queue[sr] = append(queue[sr], sc)
	dist[sr][sc] = 0

	head := 0
	for head < len(queue[sr]) || head < len(queue[1]) || head < len(queue[2]) || head < len(queue[3]) {
		done := false
		for r := 0; r < H; r++ {
			if len(queue[r]) > 0 {
				c := queue[r][0]
				queue[r] = queue[r][1:]
				currDist := dist[r][c]
				for _, nr := range []int{r - 1, r + 1} {
					if nr >= 0 && nr < H && dist[nr][c] == 1000000 {
						dist[nr][c] = currDist + 1
						queue[nr] = append(queue[nr], c)
					}
				}
				for _, nc := range []int{c - 1, c + 1} {
					if nc >= 0 && nc < W && dist[r][nc] == 1000000 {
						dist[r][nc] = currDist + 1
						queue[r] = append(queue[r], nc)
					}
				}
				done = true
			}
		}
		if !done {
			break
		}
	}

	fmt.Println(dist[tr][tc])
}

func split(s string) []string {
	var parts []string
	start := 0
	for i, c := range s {
		if c == ' ' || c == '\t' || c == '\n' || c == '\r' {
			if i > start {
				parts = append(parts, s[start:i])
			}
			start = i + 1
		}
	}
	if start < len(s) {
		parts = append(parts, s[start:])
	}
	return parts
}