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

	line, err := reader.ReadString('\n')
	if err != nil {
		return
	}
	line = strings.TrimSpace(line)
	if line == "" {
		return
	}
	tokens := strings.Fields(line)
	if len(tokens) < 4 {
		return
	}

	H, _ := strconv.Atoi(tokens[0])
	W, _ := strconv.Atoi(tokens[1])
	sr, _ := strconv.Atoi(tokens[2])
	sc, _ := strconv.Atoi(tokens[3])
	tr, _ := strconv.Atoi(tokens[4])
	tc, _ := strconv.Atoi(tokens[5])

	grid := make([]string, H)
	for i := 0; i < H; i++ {
		line, _ = reader.ReadString('\n')
		grid[i] = line
	}

	if sr < 0 || sr >= H || sc < 0 || sc >= W || tr < 0 || tr >= H || tc < 0 || tc >= W {
		fmt.Println("-1")
		return
	}

	if grid[sr][sc] == '#' || grid[tr][tc] == '#' {
		fmt.Println("-1")
		return
	}

	if sr == tr && sc == tc {
		fmt.Println("0")
		return
	}

	// BFS
	dx := []int{-1, 1, 0, 0}
	dy := []int{0, 0, -1, 1}

	dist := make([][]int, H)
	for i := range dist {
		dist[i] = make([]int, W)
		for j := range dist[i] {
			dist[i][j] = -1
		}
	}

	queue := []struct{ r, c int }{{sr, sc}}
	dist[sr][sc] = 0

	for len(queue) > 0 {
		curr := queue[0]
		queue = queue[1:]

		if curr.r == tr && curr.c == tc {
			fmt.Println(dist[tr][tc])
			return
		}

		d := dist[curr.r][curr.c] + 1
		for i := 0; i < 4; i++ {
			nr, nc := curr.r+dx[i], curr.c+dy[i]
			if nr >= 0 && nr < H && nc >= 0 && nc < W && grid[nr][nc] == '.' && dist[nr][nc] == -1 {
				dist[nr][nc] = d
				queue = append(queue, struct{ r, c int }{nr, nc})
			}
		}
	}

	fmt.Println("-1")
}